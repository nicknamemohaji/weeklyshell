/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:35:01 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/09 12:21:04 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_next_token(enum e_node_type cur, enum e_token_type next)
{
	if ((cur == EXP_IN_RWRITE || cur == EXP_IN_RAPPEND) && next != FILE_NAME)
		return (0);
	return (1);
}

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
	if (!check_next_token(exp->node_type, self->pcur_token->type))
		return (ast_syntax_error(exp));
	exp->right = parse_expression(self, precede);
	if (exp->right == NULL && self->pcur_token->type != END)
	{
		delete_ast_node(exp);
		exp = NULL;
	}
	return (exp);
}
