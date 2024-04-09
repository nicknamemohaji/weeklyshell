/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:49 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 15:07:35 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "loader.h"

int			builtin_wrapper(t_ld_exec exec, t_ld_map_env *env);
t_bool		builtin_isbuiltin(char *name);

/*
int	builtin_wrapper(t_ld_exec exec, t_ld_map_env *env)
:exec: execution infos. only use argv member variable
:env: environment variables
:return: execution result
*/
int	builtin_wrapper(t_ld_exec exec, t_ld_map_env *env)
{
	if (ft_strncmp(exec.argv[0], "cd", 2) == 0)
		return (builtin_cd(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "pwd", 3) == 0)
		return (builtin_pwd(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "echo", 4) == 0)
		return (builtin_echo(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "exit", 4) == 0)
		return (builtin_exit(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "export", 6) == 0)
		return (builtin_export(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "unset", 5) == 0)
		return (builtin_unset(exec.argv, env));
	else if (ft_strncmp(exec.argv[0], "env", 3) == 0)
		return (builtin_env(exec.argv, env));
	return (EXIT_FAILURE);
}

/*
t_bool	builtin_isbuiltin(char *name)
:name: command name to check
:return: true if command is builtin function
*/
t_bool	builtin_isbuiltin(char *name)
{
	if (ft_strncmp(name, "cd", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "pwd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "exit", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "export", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "unset", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "env", 3) == 0)
		return (TRUE);
	return (FALSE);
}
