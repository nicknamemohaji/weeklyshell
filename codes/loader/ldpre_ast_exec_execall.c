/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_exec_execall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:36:22 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/01 15:01:47 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

void	exec_prepare(t_ld_exec_nodes *node, t_ld_map_env *env);
void	exec_cleanup(t_ld_exec_nodes *node, t_ld_map_env *env);

void	exec_prepare(t_ld_exec_nodes *node, t_ld_map_env *env)
{
	t_bool			free_flag;

	while (node != NULL)
	{
		(node->exec).argv = ldpre_param_wrapper_f((node->exec).argv, env);
		(node->exec).envp = ldpre_env_toenvp_f(env);
		(node->exec).path = ldexec_exec_find_f(
				(node->exec).argv[0], &free_flag, ldpre_env_fetch("PATH", env));
		ldexec_select_type(node->exec, node, env);
		if (free_flag)
			free((node->exec).path);
		node = node->next;
	}
}

void exec_cleanup(t_ld_exec_nodes *node, t_ld_map_env *env)
{
	int				exitcode;
	t_ld_exec_nodes	*node_ptr;

	while (node != NULL)
	{
		if (node->pid > 0 && waitpid(node->pid, &exitcode, 0) < 0)
			do_exit("loader_wrapper.exec_prepare.waitpid");
		else if (node->pid == -1)
			exitcode = node->exitcode;
		else if (node->pid < 0)
			exitcode = -(node->pid);
		free_ft_split((node->exec).argv);
		free_ft_split((node->exec).envp);
		node_ptr = node;
		node = node->next;
		free(node_ptr);
	}
	ldexec_env_exitcode_update(exitcode, env);
}
