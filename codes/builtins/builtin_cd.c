/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:33 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 15:05:25 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int			builtin_cd(char *args[], t_ld_map_env *env);
static int	no_such_file_or_directory(char *path, char *pwd);

/*
int	builtin_cd(char *args[], t_ld_map_env *env)
:args: arguments
:env: environmen variables, used for changing PWD
:return: execution result (0 if cd was successful)
*/
int	builtin_cd(char *args[], t_ld_map_env *env)
{
	char	*pwd;

	if (!builtin_check_argument_count((const char **)args, 2, "cd"))
		return (EXIT_FAILURE);
	if (args[1] != NULL)
	{
		pwd = do_getcwd_f(NULL, 0);
		if (args[1][0] == '/')
		{
			if (access(args[1], F_OK | X_OK) != 0 || chdir(args[1]) != 0)
				return (no_such_file_or_directory(args[1], pwd));
		}
		else if (ft_strchr(args[1], '/') != NULL
			&& ld_chdir("cd", args[1]) != TRUE)
			return (no_such_file_or_directory(args[1], pwd));
		else if (ft_strchr(args[1], '/') == NULL && chdir(args[1]) != 0)
			return (no_such_file_or_directory(args[1], pwd));
		ldpre_env_add(ft_strdup("PWD"), do_getcwd_f(NULL, 0), env);
		free(pwd);
	}
	return (EXIT_SUCCESS);
}

/*
static int	no_such_file_or_directory(char *path, char *pwd)
:path: path failed to move into. it is from argument, so do not free this..
(arguments will be freed later)
:pwd: CWD before CD job was tried. as ld_chdir function breaks directories
and gradually changes directory, CWD even if cd was unsuccessful may have
been changed. this function will restore CWD and free the string.
:return: execution result (always 1)

used to avoid line constraint, aka 'norm function'...
*/
static int	no_such_file_or_directory(char *path, char *pwd)
{
	if (path != NULL)
		ld_errno_file("cd", path);
	chdir(pwd);
	free(pwd);
	return (EXIT_FAILURE);
}
