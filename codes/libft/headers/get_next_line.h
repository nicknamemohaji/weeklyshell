/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:15:36 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/15 13:15:42 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif 

typedef struct s_buffer
{
	int				newline_pos;
	int				length;
	char			*buffer;
	char			*buffer_ptr;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_fd
{
	int			fd;
	t_buffer	*buffer;
	struct s_fd	*next;
}	t_fd;

char		*get_next_line(int fd);
t_fd		*gnl_get_fd(int fd, t_fd *start);
t_buffer	*gnl_read_fd(t_fd *fd);
char		*gnl_read_buffer(t_buffer *start);

void		*gnl_free_fd(t_fd *fd, t_fd *list_ptr);
t_fd		*gnl_new_fd(int fd);
t_buffer	*gnl_new_buffer(int fd, int *err);
int			gnl_strlen_line(t_buffer *start);

#endif
