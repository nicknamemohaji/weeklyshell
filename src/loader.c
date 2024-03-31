/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:32:45 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:33:25 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <stdlib.h>

t_loader	*new_loader(void)
{
	t_loader	*self;

	self = malloc(sizeof(t_loader));
	if (self == NULL)
		return (NULL);
	self->cur_write_fd = -1;
	self->cur_read_fd = -1;
	self->next_read_fd = -1;
	return (self);
}

void	delete_loader(t_loader *self)
{
	free(self);
}
