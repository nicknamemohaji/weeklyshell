/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:33 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/09 15:19:52 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int			builtin_cd(char *args[], t_ld_map_env *env);
static int	no_such_file_or_directory(void);

/*
int	builtin_cd(char *args[], t_ld_map_env *env)
:args: arguments
:env: environmen variables, used for changing PWD
:return: execution result (0 if cd was successful)
*/
int	builtin_cd(char *args[], t_ld_map_env *env)
{
	if (!builtin_check_argument_count((const char **)args, 2))
		return (EXIT_FAILURE);
	if (args[1] != NULL)
	{
		if (args[1][0] == '/')
		{
			if (access(args[1], F_OK | X_OK) != 0 || chdir(args[1]) != 0)
				return (no_such_file_or_directory());
		}
		else if ((ft_strchr(args[1], '/') != NULL
				&& ld_chdir("cd", args[1]) != TRUE)
			|| (ft_strchr(args[1], '/') == NULL && chdir(args[1])))
			return (no_such_file_or_directory());
		ldpre_env_add(ft_strdup("PWD"), do_getcwd_f(NULL, 0), env);
	}
	return (EXIT_SUCCESS);
}

/*
static int	no_such_file_or_directory(void)

used to avoid line constraint, aka 'norm function'...
*/
static int	no_such_file_or_directory(void)
{
	printf("no such file or directory\n");
	return (EXIT_FAILURE);
}
