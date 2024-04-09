/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 17:46:44 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "loader.h"
#include "utils.h"

pid_t	ldexec_run_bin(t_ld_exec exec, pid_t pid);
void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
			t_ld_map_env *env, pid_t pid);

pid_t	ldexec_run_bin(t_ld_exec exec, pid_t pid)
{
	if (exec.path == NULL)
	{
		if (ft_strchr(exec.argv[0], '/') == NULL)
			write(2, "command not found\n", 18);
		return (-1);
	}
	if (pid < 0)
		pid = fork();
	if (pid < 0)
		do_exit("ldexec_run_bin.fork");
	else if (pid == 0)
	{
		errno = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (errno != 0)
			do_exit("ldexec_run_bin.signal");
		if (execve(exec.path, exec.argv, exec.envp) < 0)
			do_exit("ldexec_run_bin.execve");
	}
	return (pid);
}

void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
				t_ld_map_env *env, pid_t pid)
{
	node->exitcode = -1;
	if (builtin_isbuiltin(exec.argv[0]))
	{
		pid = -1;
		node->exitcode = builtin_wrapper(exec, env);
	}
	else
		pid = ldexec_run_bin(exec, pid);
	node->pid = pid;
}
