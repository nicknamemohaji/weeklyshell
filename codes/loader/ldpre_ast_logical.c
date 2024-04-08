/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_logical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:49:18 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/08 18:53:38 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"
#include "types.h"

int			ldpre_ast_and(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc heredoc);
int			ldpre_ast_or(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc heredoc);
static void	save_fd(int *stdin_fd, int *stdout_fd);
static void	restore_fd(int stdin_fd, int stdout_fd);

int	ldpre_ast_and(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc heredoc)
{
	int	exitcode;
	int	stdin_fd;
	int	stdout_fd;

	save_fd(&stdin_fd, &stdout_fd);
	exitcode = ldpre_ast(ast->left, env, exec, heredoc);
	restore_fd(stdin_fd, stdout_fd);
	if (exitcode == 0)
		exitcode = ldpre_ast(ast->right, env, exec, heredoc);
	return (exitcode);
}

int	ldpre_ast_or(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc heredoc)
{
	int	exitcode;
	int	stdin_fd;
	int	stdout_fd;

	save_fd(&stdin_fd, &stdout_fd);
	exitcode = ldpre_ast(ast->left, env, exec, heredoc);
	restore_fd(stdin_fd, stdout_fd);
	if (exitcode != 0)
		exitcode = ldpre_ast(ast->right, env, exec, heredoc);
	return (exitcode);
}

static void	save_fd(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FD);
	if (*stdin_fd < 0)
		do_exit("ldpre_ast_logical.dup");
	*stdout_fd = dup(STDOUT_FD);
	if (*stdout_fd < 0)
		do_exit("ldpre_ast_logical.dup");
}

static void	restore_fd(int stdin_fd, int stdout_fd)
{
	close(STDIN_FD);
	if (dup(stdin_fd) < 0)
		do_exit("ldpre_ast_logical.dup");
	close(stdin_fd);
	close(STDOUT_FD);
	if (dup(stdout_fd) < 0)
		do_exit("ldpre_ast_logical.dup");
	close(stdout_fd);
}
