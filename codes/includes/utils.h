/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:54:44 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/13 21:10:22 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"
# include "types.h"

// free_ft_split.c
void	free_ft_split(char **ptr);

// ld_chdir.c
t_bool	ld_chdir(char *path);

// do_exit.c
void	do_exit(char *errorstr);

#endif
