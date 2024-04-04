/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:31:08 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/04 11:38:28 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*parse_prefix_exp(t_parser *self, int node_type)
{
	t_ast_node	*exp;

	exp = new_ast_node();
	if (exp == NULL)
		return (ast_malloc_error(exp));
	exp->node_type = node_type;
	move_next_token(self);
	exp->left = parse_file(self);
	move_next_token(self);
	exp->right = parse_expression(self, P_PREFIX);
	if (exp->left == NULL || (self->pcur_token->type != END
			&& exp->right == NULL))
	{
		delete_ast_node(exp);
		exp = NULL;
	}
	return (exp);
}

t_ast_node	*parse_prefix(t_parser *self)
{
	int	node_type;

	node_type = get_prefix_node_type(self->pcur_token->type);
	if (self->pcur_token->type == LPAR)
		return (parse_parenthesis(self));
	else if (node_type == NODE_ERROR)
		return (ast_syntax_error(NULL));
	else if (node_type == NODE_FILE)
		return (parse_file(self));
	else if (node_type == NODE_WORD)
		return (parse_command(self));
	return (parse_prefix_exp(self, node_type));
}
