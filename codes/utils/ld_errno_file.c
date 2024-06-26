/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_errno_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:33:48 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/22 14:47:49 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "types.h"

t_bool	ld_errno_file(const char *trace, char *path);

/*
t_bool	ld_errno_file(const char *trace, char *path)
:param trace: function info
:param path: file that had error
:return: always returns FALSE, because this function will be used in 
return statement.

prints error message to STDOUT if recovable (ex. ENOENT, EACCESS),
exits if error is unrecovable (ex. EIO, EFAULT)
*/
t_bool	ld_errno_file(const char *trace, char *path)
{
	if (errno == ENOENT)
		ft_dprintf(2, "%s: %s: No such file or directory\n", trace, path);
	else if (errno == ENOTDIR)
		ft_dprintf(2, "%s: %s: Not a directory\n", trace, path);
	else if (errno == EISDIR)
		ft_dprintf(2, "%s: %s: Is a directory\n", trace, path);
	else if (errno == EACCES)
		ft_dprintf(2, "%s: %s: Permission denied\n", trace, path);
	else if (errno == ENAMETOOLONG)
		ft_dprintf(2, "%s: %s: Name too long\n", trace, path);
	else
		do_exit(trace);
	return (FALSE);
}
