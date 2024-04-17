/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:13:08 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 20:30:59 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool			ld_chdir(const char *trace, char *path);
static t_bool	check_access(const char *trace, char *path);

/*
t_bool	ld_chdir(const char *trace, char *path)
:param path: path to move 
:return: TRUE if it was able to move to the pat
*/
t_bool	ld_chdir(const char *trace, char *path)
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
	while (++idx < count)
	{
		if (check_access(trace, splitted_path[idx]) == FALSE)
		{
			free_ft_split(splitted_path_ptr);
			return (FALSE);
		}
	}
	free_ft_split(splitted_path_ptr);
	return (TRUE);
}

/*
static t_bool	check_access(const char *trace, char *path)
:param path: path to check access
*/
static t_bool	check_access(const char *trace, char *path)
{
	errno = 0;
	if (access(path, F_OK | X_OK) != 0)
		return (ld_errno_file(trace, path));
	if (chdir(path) != 0)
		return (ld_errno_file(trace, path));
	return (TRUE);
}
