/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:35:01 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/31 16:50:02 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_infix(t_parser *self, t_ast_node *left)
{
	t_ast_node	*exp;
	int			precede;

	exp = new_ast_node();
	if (exp == NULL)
		return (ast_malloc_error(left));
	exp->node_type = get_infix_node_type(self->pcur_token->type);
	exp->left = left;
	precede = get_precedence(self->pcur_token->type);
	move_next_token(self);
	exp->right = parse_expression(self, precede);
	if (exp->right == NULL)
	{
		delete_ast_node(exp);
		exp = NULL;
	}
	return (exp);
}
