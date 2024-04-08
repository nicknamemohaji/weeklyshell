/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_exec_execall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:36:22 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/08 18:47:46 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int	exec_cleanup(t_ld_exec_nodes *node, t_ld_map_env *env, t_bool free_flag);

int	exec_cleanup(t_ld_exec_nodes *node, t_ld_map_env *env, t_bool free_flag)
{
	int				exitcode;
	t_ld_exec_nodes	*node_ptr;

	while (node != NULL)
	{
		// TODO builtin들의 exit code가 제대로 수집되지 않음
		if (node->pid > 0 && waitpid(node->pid, &exitcode, 0) < 0)
			do_exit("loader_wrapper.exec_prepare.waitpid");
		else if (node->pid == -1)
			exitcode = node->exitcode;
		else if (node->pid < 0)
			exitcode = -(node->pid);
		free_ft_split((node->exec).argv);
		free_ft_split((node->exec).envp);
		if (free_flag)
			free((node->exec).path);
		node_ptr = node;
		node = node->next;
		free(node_ptr);
	}
	ldexec_env_exitcode_update(exitcode, env);
	return (exitcode);
}
