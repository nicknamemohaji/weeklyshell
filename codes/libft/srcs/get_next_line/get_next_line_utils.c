/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:21:13 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 01:30:18 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		*gnl_free_fd(t_fd *fd, t_fd *list_ptr);
t_fd		*gnl_new_fd(int fd);
t_buffer	*gnl_new_buffer(int fd, int *err);
int			gnl_strlen_line(t_buffer *start);

t_fd	*gnl_new_fd(int fd)
{
	t_fd	*new_fd;

	new_fd = malloc(1 * sizeof(t_fd));
	if (new_fd == NULL)
		return (NULL);
	new_fd->fd = fd;
	new_fd->next = NULL;
	new_fd->buffer = gnl_new_buffer(fd, NULL);
	if (new_fd->buffer == NULL)
	{
		free(new_fd);
		return (NULL);
	}
	return (new_fd);
}

void	*gnl_free_fd(t_fd *fd, t_fd *list_ptr)
{
	t_fd		*list;
	t_buffer	*buffer;

	list = list_ptr;
	while (list->next != fd)
		list = list->next;
	list->next = fd->next;
	if (fd->buffer != NULL)
	{
		while (fd->buffer != NULL)
		{
			buffer = fd->buffer;
			fd->buffer = (fd->buffer)->next;
			free(buffer->buffer_ptr);
			free(buffer);
		}
	}
	free(fd);
	return (NULL);
}

t_buffer	*gnl_new_buffer(int fd, int *err)
{
	t_buffer	*new_buffer;

	new_buffer = malloc(1 * sizeof(t_buffer));
	if (new_buffer == NULL)
		return (NULL);
	new_buffer->buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (new_buffer->buffer == NULL)
	{
		free(new_buffer);
		return (NULL);
	}
	new_buffer->buffer_ptr = new_buffer->buffer;
	new_buffer->next = NULL;
	new_buffer->length = read(fd, new_buffer->buffer, BUFFER_SIZE);
	new_buffer->newline_pos = -1;
	if (new_buffer->length <= 0)
	{
		if (err != NULL)
			*err = new_buffer->length;
		free(new_buffer->buffer);
		free(new_buffer);
		return (NULL);
	}
	return (new_buffer);
}

int	gnl_strlen_line(t_buffer *start)
{
	int		size;
	int		cnt;
	char	*buffer;

	size = 0;
	while (start != NULL)
	{
		buffer = start->buffer;
		cnt = start->length;
		while (cnt > 0 && *buffer != '\n')
		{
			cnt--;
			size++;
			buffer++;
		}
		if (cnt > 0 && *buffer == '\n')
		{
			size++;
			break ;
		}
		start = start->next;
	}
	return (size);
}
