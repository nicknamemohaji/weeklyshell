/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:14 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/18 19:14:51 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"
# include "types.h"

// ldexec_findexec.c
char	*ldexec_exec_find_f(char *cmd, t_bool *need_free, const char *path);

// ldexec_run.c
int		ldexec_run(t_ld_struct_exec exec);

// ldexec_heredoc.c
char	*ldexec_heredoc_assign(void);
t_bool	ldexec_heredoc(int fd, char *delim);

#endif
