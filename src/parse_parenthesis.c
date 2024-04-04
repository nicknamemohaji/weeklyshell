/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:33:42 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/04 16:54:09 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	subshell

	create subshell node as a root of subtree
*/
t_ast_node	*parse_parenthesis(t_parser *self)
{
	t_ast_node	*subshell;

	subshell = new_ast_node();
	if (subshell == NULL)
		return (ast_malloc_error(subshell));
	subshell->node_type = EXP_SUBSHELL;
	move_next_token(self);
	subshell->left = parse_expression(self, P_LOWEST);
	move_next_token(self);
	if (subshell->left == NULL)
	{
		delete_ast_node(subshell);
		return (NULL);
	}
	else if (self->pcur_token->type != RPAR)
		return (ast_syntax_error(subshell));
	return (subshell);
}
