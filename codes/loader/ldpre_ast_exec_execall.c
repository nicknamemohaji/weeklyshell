/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_exec_execall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:36:22 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/17 23:06:34 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int			exec_cleanup(t_ld_exec_nodes *node,
				t_ld_map_env *env, t_bool free_flag);
static void	free_env(t_ld_exec exec, t_bool free_flag);

int	exec_cleanup(t_ld_exec_nodes *node, t_ld_map_env *env, t_bool free_flag)
{
	int				exitcode;
	t_ld_exec_nodes	*node_ptr;

	while (node != NULL)
	{
		if (node->pid > 0 && waitpid(node->pid, &exitcode, 0) < 0)
			do_exit("loader_wrapper.exec_prepare.waitpid");
		if (node->pid > 0 && node->pid > 0 && WIFSIGNALED(exitcode))
		{
			exitcode = 128 + WTERMSIG(exitcode);
			write(1, "\n", 1);
		}
		else if (node->pid > 0)
			exitcode = WEXITSTATUS(exitcode);
		if (node->pid < 0 && node->exitcode >= 0)
			exitcode = node->exitcode;
		else if (node->pid < 0)
			exitcode = 1;
		free_env(node->exec, free_flag);
		node_ptr = node;
		node = node->next;
		free(node_ptr);
	}
	ldexec_env_exitcode_update(exitcode, env);
	return (exitcode);
}

static void	free_env(t_ld_exec exec, t_bool free_flag)
{
	free_ft_split(exec.argv);
	free_ft_split(exec.envp);
	if (free_flag)
		free(exec.path);
}
