/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_findexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 00:02:33 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "loader.h"

char		*ldexec_exec_find_f(char *cmd,
				t_bool *need_free, const char *path);
static char	*check_relative_f(char *cmd);	
static char	*check_cwd_f(char *cmd);
static char	*check_env_path_f(char *cmd, const char *path);

/*
char	*ldexec_exec_find_f(char *cmd, t_bool *need_free, const char *path)
:param cmd: binary name to check
:param need_free: if returned path is allocated in this function, callee should
free the pointer. if path is absolute path, it should not be freed, so always
check value of need_free variable before freeing.
:param path: `$PATH` environment variable
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary

Find executable path on [absolute path / relative path / CWD / $PATH environ]
It's caller's responsibility to free the returned pointer after use,
depending on need_free's value.

NOTE) It only checks existence and permission.
Callee should use calls like stat(2) to check it is an executable.
*/
char	*ldexec_exec_find_f(char *cmd, t_bool *need_free, const char *path)
{
	char	*ret;

	*need_free = TRUE;
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (*cmd == '/')
		{
			*need_free = FALSE;
			if (access(cmd, F_OK | X_OK) == 0)
				return (cmd);
			else
				return (NULL);
		}
		else
			return (check_relative_f(cmd));
	}
	ret = check_cwd_f(cmd);
	if (ret != NULL)
		return (ret);
	ret = check_env_path_f(cmd, path);
	return (ret);
}

/*
static char	*check_relative_f(char *cmd)
:param cmd: binary name to check
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary
*/
static char	*check_relative_f(char *cmd)
{
	char	*cwd_prev;
	char	*real_cmd;
	char	*ret;
	int		idx;

	cwd_prev = getcwd(NULL, 0);
	if (cwd_prev == NULL)
		do_exit("ldexec_findexec.check_relaive_f.getcwd");
	if (ld_chdir(cmd) != TRUE)
		ret = NULL;
	else
	{
		idx = ft_strrchr(cmd, '/') - cmd + 1;
		real_cmd = ft_substr(cmd, idx, (ft_strlen(cmd) - idx));
		ret = check_cwd_f(real_cmd);
		free(real_cmd);
	}
	if (chdir(cwd_prev) != 0)
		do_exit("ldexec_findexec.check_relaive_f.chdir");
	free(cwd_prev);
	return (ret);
}

/*
static char	*check_cwd_f(char *cmd)
:param cmd: binary name to check
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary
*/
static char	*check_cwd_f(char *cmd)
{
	char	*cwd;
	char	*cwd_with_slash;
	char	*cmd_with_cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		do_exit("ldexec_findexec.check_cwd_f.getcwd");
	cwd_with_slash = ft_strjoin(cwd, "/");
	cmd_with_cwd = ft_strjoin(cwd_with_slash, cmd);
	free(cwd);
	free(cwd_with_slash);
	printf("checking %s\n", cmd_with_cwd);
	if (access(cmd_with_cwd, F_OK | X_OK) == 0)
		return (cmd_with_cwd);
	free(cmd_with_cwd);
	return (NULL);
}

/*
static char	*check_env_path_f(char *cmd, const char *path)
:param cmd: binary name to check
:param path: `$PATH` environment variable
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary
*/
static char	*check_env_path_f(char *cmd, const char *path)
{
	char	**paths;
	char	**paths_ptr;
	char	*path_with_slash;
	char	*cmd_with_path;
	char	*ret;

	ret = NULL;
	paths = ft_split(path, ':');
	paths_ptr = paths;
	while (*(paths++) != NULL)
	{
		path_with_slash = ft_strjoin(*(paths - 1), "/");
		cmd_with_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(cmd_with_path, F_OK | X_OK) == 0)
		{
			ret = cmd_with_path;
			break ;
		}
		free(cmd_with_path);
	}
	free_ft_split(paths_ptr);
	return (ret);
}
