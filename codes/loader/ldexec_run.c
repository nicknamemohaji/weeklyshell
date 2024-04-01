/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/01 15:18:19 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "loader.h"
#include "utils.h"

pid_t	ldexec_run_bin(t_ld_exec exec);
void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
				t_ld_map_env *env);

pid_t	ldexec_run_bin(t_ld_exec exec)
{
	pid_t	pid;

	if (exec.path == NULL)
	{
		printf("command not found\n");
		return (-127);
	}
	pid = fork();
	if (pid < 0)
		do_exit("ldexec_run_bin.fork");
	else if (pid == 0)
	{
		if (execve(exec.path, exec.argv, exec.envp) < 0)
			do_exit("ldexec_run_bin.execve");
	}
	return (pid);
}

void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
				t_ld_map_env *env)
{
	pid_t	pid;

	printf("argv %s\n", exec.argv[0]);
	printf("path %s\n", exec.path);
	if (builtin_isbuiltin(exec.argv[0]))
	{
		// TODO builtin in subshell environment
		if (FALSE)
		{
			pid = fork();
			if (pid == 0)
				exit(builtin_wrapper(exec, env));
		}
		else
		{
			pid = -1;
			node->exitcode = builtin_wrapper(exec, env);
		}
	}
	else
			pid = ldexec_run_bin(exec);
	node->pid = pid;
}
