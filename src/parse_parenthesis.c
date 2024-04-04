/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:33:42 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/31 16:49:28 by dogwak           ###   ########.fr       */
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
	if (subshell->left == NULL || self->pcur_token->type != RPAR)
		return (ast_syntax_error(subshell));
	return (subshell);
}
