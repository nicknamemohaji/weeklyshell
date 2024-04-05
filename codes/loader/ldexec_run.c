/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 16:25:50 by kyungjle         ###   ########.fr       */
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
	// TODO pipe subshell인지 감지, fork를 하지 않음
	if (pid < 0)
		do_exit("ldexec_run_bin.fork");
	else if (pid == 0)
	{
		if (signal(SIGINT, SIG_DFL) < 0)
			do_exit("ldexec_run_bin.signal");
		if (signal(SIGKILL, SIG_DFL) < 0)
			do_exit("ldexec_run_bin.signal");
		if (execve(exec.path, exec.argv, exec.envp) < 0)
			do_exit("ldexec_run_bin.execve");
	}
	return (pid);
}

void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
				t_ld_map_env *env)
{
	pid_t	pid;

	if (builtin_isbuiltin(exec.argv[0]))
	{
		pid = -1;
		node->exitcode = builtin_wrapper(exec, env);
	}
	else
			pid = ldexec_run_bin(exec);
	node->pid = pid;
}
