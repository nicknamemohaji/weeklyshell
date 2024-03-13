/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:13:08 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/13 21:10:22 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool			ld_chdir(char *path);
static t_bool	check_access(char *path);

t_bool	ld_chdir(char *path)
{
	char	**splitted_path;
	char	**splitted_path_ptr;
	int		count;
	int		idx;

	splitted_path = ft_split(path, '/');
	splitted_path_ptr = splitted_path;
	count = 0;
	while (*(splitted_path++) != NULL)
		count++;
	splitted_path = splitted_path_ptr;
	idx = -1;
	while (++idx < count - 1)
	{
		printf("moving to %s\n", splitted_path[idx]);
		if (check_access(splitted_path[idx]) == FALSE)
		{
			free_ft_split(splitted_path_ptr);
			return (FALSE);
		}
		if (chdir(splitted_path[idx]) != 0)
			do_exit("ld_chdir.chdir");
	}
	free_ft_split(splitted_path_ptr);
	return (TRUE);
}

static t_bool	check_access(char *path)
{
	errno = 0;
	if (access(path, F_OK | X_OK) != 0)
	{
		if (errno == ENOENT)
			printf("ld_chdir: %s: no such file\n", path);
		else if (errno == ENOTDIR)
			printf("ld_chdir: %s: not a directory\n", path);
		else if (errno == EACCES)
			printf("ld_chdir: %s: permission denied\n", path);
		else
			do_exit("ld_chdir.check_access.access");
		return (FALSE);
	}
	else
		return (TRUE);
}
