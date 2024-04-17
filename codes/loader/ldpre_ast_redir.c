/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:56:03 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/17 14:29:12 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int	ldpre_ast_wopen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
int	ldpre_ast_ropen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
int	ldpre_ast_wpopen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

int	ldpre_ast_wopen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	t_bool	left_isfile;

	if (env->should_postpone)
		return (-1);
	left_isfile = FALSE;
	if (ast->left != NULL && (ast->left)->node_type == NODE_FILE)
	{
		left_isfile = TRUE;
		if (ldpre_ast_redir_outfile((ast->left)->pcmd[0],
				ast->node_type) == FALSE)
			return (-1);
	}
	if ((ast->right)->node_type == NODE_FILE)
	{
		if (ldpre_ast_redir_outfile((ast->right)->pcmd[0],
				ast->node_type) == FALSE)
			return (-1);
	}
	else if (ldpre_ast(ast->right, env, exec, heredoc) < 0)
		return (-1);
	if (!left_isfile)
		return (ldpre_ast(ast->left, env, exec, heredoc));
	return (0);
}

int	ldpre_ast_ropen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	t_bool	right_isfile;

	if (env->should_postpone)
		return (-1);
	right_isfile = FALSE;
	if (ast->right != NULL && (ast->right)->node_type == NODE_FILE)
	{
		right_isfile = TRUE;
		if (ldpre_ast_redir_infile((ast->right)->pcmd[0],
				heredoc, ast->node_type, env) == FALSE)
			return (-1);
	}
	if ((ast->left)->node_type == NODE_FILE)
	{
		if (ldpre_ast_redir_infile((ast->left)->pcmd[0],
				heredoc, ast->node_type, env) == FALSE)
			return (-1);
	}
	else if (ldpre_ast(ast->left, env, exec, heredoc) < 0)
		return (-1);
	if (!right_isfile)
		return (ldpre_ast(ast->right, env, exec, heredoc));
	return (0);
}

int	ldpre_ast_wpopen(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	t_bool	right_isfile;

	if (env->should_postpone)
		return (-1);
	right_isfile = FALSE;
	if (ast->right != NULL && (ast->right)->node_type == NODE_FILE)
	{
		right_isfile = TRUE;
		if (ldpre_ast_redir_outfile((ast->right)->pcmd[0],
				ast->node_type) == FALSE)
			return (-1);
	}
	if ((ast->left)->node_type == NODE_FILE)
	{
		if (ldpre_ast_redir_outfile((ast->left)->pcmd[0],
				ast->node_type) == FALSE)
			return (-1);
	}
	else if (ldpre_ast(ast->left, env, exec, heredoc) < 0)
		return (-1);
	if (!right_isfile && ast->right != NULL)
		return (ldpre_ast(ast->right, env, exec, heredoc));
	return (0);
}
