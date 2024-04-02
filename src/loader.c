/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:32:45 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/02 18:47:26 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <stdlib.h>

int construct_pid(void *pos, void *param)
{
	*(int *)pos = *(int *)param;
	return (1);
}

void destruct_pid(void *pid_ptr)
{
	pid_ptr++;
}

t_loader	*new_loader(void)
{
	t_loader	*self;

	self = malloc(sizeof(t_loader));
	if (self == NULL)
		return (NULL);
	self->p_pid_vec = new_ftvec(construct_pid, destruct_pid, sizeof(int));
	if (self->p_pid_vec == NULL)
	{
		free(self);
		return (NULL);
	}
	self->cur_write_fd = -1;
	self->cur_read_fd = -1;
	self->next_read_fd = -1;
	return (self);
}

void	delete_loader(t_loader *self)
{
	free(self);
}
