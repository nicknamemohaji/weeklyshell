/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:04:57 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 18:21:15 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"
#include "types.h"

int						ldpre_ast_exec(t_ast_node *ast, t_ld_map_env *env,
							t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
static t_ld_exec_nodes	*prepare_exec(char **pcmd,
							t_ld_map_env *env, t_bool *free_flag);
static int				exec_child(t_ld_exec_nodes *node, pid_t pid,
							t_bool free_flag, t_ld_map_env *env);

int	ldpre_ast_exec(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	t_ld_exec_nodes	*node;
	t_bool			free_flag;
	pid_t			pid;

	(void) heredoc;
	node = prepare_exec(ast->pcmd, env, &free_flag);
	pid = -1;
	if (exec != NULL)
	{
		pid = fork();
		if (pid < 0)
			do_exit("ldpre_ast.fork");
	}
	if (exec == NULL || pid == 0)
		return (exec_child(node, pid, free_flag, env));
	else
	{
		node->pid = pid;
		while (exec->next != NULL)
			exec = exec->next;
		exec->next = node;
		if (free_flag)
			free(node->exec.path);
		return (0);
	}
}

static t_ld_exec_nodes	*prepare_exec(char **pcmd,
							t_ld_map_env *env, t_bool *free_flag)
{
	t_ld_exec_nodes	*node;

	node = malloc(1 * sizeof(t_ld_exec_nodes));
	if (node == NULL)
		do_exit("ldpre_ast.malloc");
	node->next = NULL;
	(node->exec).argv = ldpre_param_wrapper_f(pcmd, env);
	(node->exec).envp = ldpre_env_toenvp_f(env);
	(node->exec).path = ldexec_exec_find_f(
			(node->exec).argv[0], free_flag, ldpre_env_fetch("PATH", env));
	return (node);
}

static int	exec_child(t_ld_exec_nodes *node, pid_t pid,
				t_bool free_flag, t_ld_map_env *env)
{
	int	exitcode;

	ldexec_select_type(node->exec, node, env, pid);
	exitcode = exec_cleanup(node, env, free_flag);
	if (pid == 0)
		exit(exitcode);
	return (exitcode);
}
