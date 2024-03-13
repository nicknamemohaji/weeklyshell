/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_errno_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:33:48 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/14 01:45:23 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ld_errno_file(char *trace, char *path);

void	ld_errno_file(char *trace, char *path)
{
	if (errno == ENOENT)
		printf("%s: %s: no such file\n", trace, path);
	else if (errno == ENOTDIR)
		printf("%s: %s: not a directory\n", trace, path);
	else if (errno == EISDIR)
		printf("%s: %s: is a directory\n", trace, path);
	else if (errno == EACCES)
		printf("%s: %s: permission denied\n", trace, path);
	else if (errno == ENAMETOOLONG)
		printf("%s: %s: name too long\n", trace, path);
	else
		do_exit(trace);
}
