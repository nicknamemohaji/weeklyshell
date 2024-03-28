/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:35:24 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:35:28 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	evaluate_ast(t_loader *ld, const t_ast_node *node)
{
	if (node->node_type == EXP_SUBSHELL)
		return (evaluate_subshell(ld, node));
	else if (node->node_type == EXP_IN_PIPE)
		return (evaluate_infix_pipe(ld, node));
	else if (node->node_type == EXP_IN_AND)
		return (evaluate_infix_and(ld, node));
	else if (node->node_type == EXP_IN_OR)
		return (evaluate_infix_or(ld, node));
	else if (node->node_type == EXP_IN_RWRITE)
		return (evaluate_infix_rwrite(ld, node));
	else if (node->node_type == EXP_IN_RAPPEND)
		return (evaluate_infix_rappend(ld, node));
	else if (node->node_type == EXP_PRE_RREAD)
		return (evaluate_prefix_rread(ld, node));
	else if (node->node_type == EXP_PRE_RHEREDOC)
		return (evaluate_prefix_rheredoc(ld, node));
	else if (node->node_type == EXP_PRE_RWRITE)
		return (evaluate_prefix_rwrite(ld, node));
	else if (node->node_type == EXP_PRE_RAPPEND)
		return (evaluate_prefix_rappend(ld, node));
	else if (node->node_type == NODE_COMMAND)
		return (execute_command(ld, node));
	else
		return (0);
}
