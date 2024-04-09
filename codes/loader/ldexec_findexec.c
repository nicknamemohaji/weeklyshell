/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_findexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 15:20:07 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "loader.h"

char		*ldexec_exec_find_f(char *cmd,
				t_bool *need_free, const char *path);
static char	*check_relative_f(char *cmd);	
static char	*check_cwd_f(char *cmd);
static char	*check_env_path_f(char *cmd, const char *path);
static char	*check_env_path_bin_f(char *cmd, char *path);

/*
char	*ldexec_exec_find_f(char *cmd, t_bool *need_free, const char *path)
:param cmd: binary name to check
:param need_free: if returned path is allocated in this function, callee should
free the pointer. but if cmd was absolute path, then returned path
should not be freed. writes FALSE to callee if cmd was absolute path, else TRUE
if string buffer was mallocated in this function.
:param path: `$PATH` environment variable
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary

Finds executable path on [absolute path / relative path / CWD / $PATH environ]
- if cmd contains `/`, check absolute path + relative path
- else check CWD + $PATH environ

Caller should free the returned pointer after use,
depending on need_free's value.
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
			else if (errno != EACCES && errno != ENOENT)
				do_exit("ldexec_exec_find_f.access");
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

	cwd_prev = do_getcwd_f(NULL, 0);
	if (cwd_prev == NULL)
		do_exit("ldexec_findexec.check_relaive_f.getcwd");
	ret = ft_substr(cmd, 0, ft_strrchr(cmd, '/') - cmd);
	if (ld_chdir("weeklyshell", ret) != TRUE)
		ret = NULL;
	free(ret);
	if (ret != NULL)
	{
		idx = ft_strrchr(cmd, '/') - cmd + 1;
		real_cmd = ft_substr(cmd, idx, (ft_strlen(cmd) - idx));
		if (real_cmd == NULL)
			do_exit("ldexec_findexec.check_relative_f.malloc");
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

	cwd = do_getcwd_f(NULL, 0);
	if (cwd == NULL)
		do_exit("ldexec_findexec.check_cwd_f.getcwd");
	cwd_with_slash = ft_strjoin(cwd, "/");
	if (cwd_with_slash == NULL)
		do_exit("ldexec_findexec.check_cwd_f.malloc");
	cmd_with_cwd = ft_strjoin(cwd_with_slash, cmd);
	if (cmd_with_cwd == NULL)
		do_exit("ldexec_findexec.check_cwd_f.malloc");
	free(cwd);
	free(cwd_with_slash);
	if (access(cmd_with_cwd, F_OK | X_OK) == 0)
		return (cmd_with_cwd);
	else if (errno != EACCES && errno != ENOENT)
		do_exit("ldexec_findexec.check_cwd_f.access");
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
	char	*ret;

	ret = NULL;
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		do_exit("ldexec_findexec.check_env_path_f.malloc");
	paths_ptr = paths;
	while (*(paths++) != NULL)
	{
		ret = check_env_path_bin_f(cmd, *(paths - 1));
		if (ret != NULL)
			break ;
	}
	free_ft_split(paths_ptr);
	return (ret);
}

/*
static char	*check_env_path_bin_f(char *cmd, const char *path)
:param cmd: binary name to check
:param path: specific PATH to check
:return: NULL if matching executable is not found, else string(char *)
containing absolute location of the binary

I HATE NORM's LINE CONSTRAINT!!!
*/
static char	*check_env_path_bin_f(char *cmd, char *path)
{
	char	*path_with_slash;
	char	*cmd_with_path;

	path_with_slash = ft_strjoin(path, "/");
	if (path_with_slash == NULL)
		do_exit("ldexec_findexec.check_env_path_bin_f.malloc");
	cmd_with_path = ft_strjoin(path_with_slash, cmd);
	if (cmd_with_path == NULL)
		do_exit("ldexec_findexec.check_env_path_bin_f.malloc");
	free(path_with_slash);
	if (access(cmd_with_path, F_OK | X_OK) == 0)
		return (cmd_with_path);
	else if (errno != EACCES && errno != ENOENT)
		do_exit("ldexec_findexec.check_env_path_bin_f.access");
	else
		free(cmd_with_path);
	return (NULL);
}
