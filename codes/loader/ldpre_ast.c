/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:20:45 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 15:14:44 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "parser.h"
#include "types.h"
#include "utils.h"

int	ldpre_ast(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	if (ast->node_type == NODE_COMMAND)
		return (ldpre_ast_exec(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_SUBSHELL)
		return (ldpre_ast_subshell(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_IN_PIPE)
		return (ldpre_ast_pipe(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_IN_AND)
		return (ldpre_ast_and(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_IN_OR)
		return (ldpre_ast_or(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_IN_RWRITE
		|| ast->node_type == EXP_IN_RAPPEND)
		return (ldpre_ast_wopen(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_PRE_RREAD
		|| ast->node_type == EXP_PRE_RHEREDOC)
		return (ldpre_ast_ropen(ast, env, exec, heredoc));
	else if (ast->node_type == EXP_PRE_RAPPEND
		|| ast->node_type == EXP_PRE_RWRITE)
		return (ldpre_ast_wpopen(ast, env, exec, heredoc));
	printf("unknown node type..!!! %d %s", ast->node_type, ast->pcmd[0]);
	return (-42);
}
