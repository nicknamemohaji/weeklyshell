/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:07:19 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/29 19:11:02 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_expression(t_parser *self, int precede)
{
	t_ast_node	*left_exp;
	int			next_node_type;

	if ((size_t)self->cur_idx == self->ptoken_stream->size)
		return (ast_syntax_error(NULL));
	if (self->pcur_token->type == END)
		return (NULL);
	left_exp = parse_prefix(self);
	while (self->pcur_token->type != END && left_exp != NULL
		&& (size_t)self->cur_idx < self->ptoken_stream->size - 2
		&& precede < get_precedence(self->pnext_token->type))
	{
		next_node_type = get_infix_node_type(self->pnext_token->type);
		if (next_node_type == NODE_ERROR)
			return (ast_syntax_error(left_exp));
		else
		{
			move_next_token(self);
			left_exp = parse_infix(self, left_exp);
			if (left_exp == NULL)
				break ;
		}
	}
	return (left_exp);
}
