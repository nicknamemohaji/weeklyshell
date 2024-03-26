/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:22:54 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 01:30:20 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
t_fd		*gnl_get_fd(int fd, t_fd *start);
t_buffer	*gnl_read_fd(t_fd *fd);
char		*gnl_read_buffer(t_buffer *start);

char	*get_next_line(int _fd)
{
	static t_fd	fd_list = {.fd = -1, .next = NULL, .buffer = NULL};
	t_fd		*fd;
	t_buffer	*buffer;
	char		*res;

	fd = gnl_get_fd(_fd, &fd_list);
	if (fd == NULL)
		return (NULL);
	buffer = gnl_read_fd(fd);
	if (buffer == NULL)
		return (gnl_free_fd(fd, &fd_list));
	res = gnl_read_buffer(buffer);
	if (res == NULL)
		return (gnl_free_fd(fd, &fd_list));
	while (fd->buffer != NULL && (fd->buffer)->length == 0)
	{
		buffer = fd->buffer;
		fd->buffer = (fd->buffer)->next;
		free(buffer->buffer_ptr);
		free(buffer);
	}
	if (fd->buffer == NULL)
		gnl_free_fd(fd, &fd_list);
	return (res);
}

t_fd	*gnl_get_fd(int fd, t_fd *list)
{
	t_fd	*new_fd;
	t_fd	*node;

	if (fd < 0)
		return (NULL);
	node = list;
	while (node != NULL)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	new_fd = gnl_new_fd(fd);
	if (new_fd == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	list->next = new_fd;
	return (new_fd);
}

t_buffer	*gnl_read_fd(t_fd *fd)
{
	t_buffer	*next;
	char		*buffer;
	int			cnt;
	int			err;

	next = fd->buffer;
	while (next != NULL)
	{
		buffer = next->buffer;
		cnt = next->length;
		while (cnt-- > 0)
		{
			if (*(buffer++) == '\n')
			{
				next->newline_pos = buffer - next->buffer_ptr;
				return (fd->buffer);
			}
		}
		next->next = gnl_new_buffer(fd->fd, &err);
		if (next->next == NULL && next->length > 0 && err == 0)
			return (fd->buffer);
		next = next->next;
	}
	return (NULL);
}

char	*gnl_read_buffer(t_buffer *start)
{
	char	*res;
	char	*res_ptr;
	int		size;

	size = gnl_strlen_line(start);
	res = malloc((size + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res_ptr = res;
	while (size > 0)
	{
		while (start->length > 0 && size > 0)
		{
			*res = *(start->buffer);
			(start->buffer)++;
			(start->length)--;
			size--;
			res++;
		}
		start = start->next;
	}
	*res = 0;
	return (res_ptr);
}
