/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:08:37 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 13:08:43 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*new_parser(t_ft_vector *ptstream)
{
	t_parser	*p;

	p = (t_parser *)malloc(sizeof(t_parser));
	p->cur_idx = 0;
	p->ptoken_stream = ptstream;
	p->pcur_token = ptstream->at(ptstream, 0);
	p->pnext_token = ptstream->at(ptstream, 0);
	return (p);
}

void	delete_parser(t_parser *self)
{
	delete_ftvec(self->ptoken_stream);
	free(self);
}

void	move_next_token(t_parser *self)
{
	if (self->cur_idx < self->ptoken_stream->size - 1)
	{
		self->cur_idx++;
		self->pcur_token = self->ptoken_stream->at(self->ptoken_stream,
				self->cur_idx);
		self->pnext_token = self->ptoken_stream->at(self->ptoken_stream,
				self->cur_idx + 1);
	}
	else if (self->cur_idx == self->ptoken_stream->size - 1)
	{
		self->cur_idx = self->ptoken_stream->size - 1;
		self->pcur_token = self->ptoken_stream->at(self->ptoken_stream,
				self->cur_idx);
		self->pnext_token = NULL;
	}
	else
	{
		self->cur_idx = self->ptoken_stream->size;
		self->pcur_token = NULL;
		self->pnext_token = NULL;
	}
}
