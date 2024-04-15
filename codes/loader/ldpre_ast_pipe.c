/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:08:58 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 17:27:15 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int			ldpre_ast_pipe(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
static void	redirect_fd(int *fd_preserve, int fd_target, int fd_redirect);
static void	restore_fd(int fd_preserve, int fd_target);
static int	run_pipe(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

int	ldpre_ast_pipe(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	t_ld_exec_nodes	start;

	if (exec == NULL)
	{
		start.next = NULL;
		run_pipe(ast, env, &start, heredoc);
		return (exec_cleanup(start.next, env, FALSE));
	}
	else
		return (run_pipe(ast, env, exec, heredoc));
}

static void	redirect_fd(int *fd_preserve, int fd_target, int fd_redirect)
{
	*fd_preserve = dup(fd_target);
	if (*fd_preserve < 0)
		do_exit("ldpre_ast_pipe.dup");
	close(fd_target);
	if (dup(fd_redirect) < 0)
		do_exit("ldpre_ast_pipe.dup");
	close(fd_redirect);
}

static void	restore_fd(int fd_preserve, int fd_target)
{
	close(fd_target);
	if (dup(fd_preserve) < 0)
		do_exit("ldpre_ast_pipe.dup");
	close(fd_preserve);
}

static int	run_pipe(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	int	preserve_fd[2];
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		do_exit("ldpre_ast_pipe.pipe");
	redirect_fd(&preserve_fd[1], STDOUT_FD, pipe_fd[1]);
	ldpre_ast(ast->left, env, exec, heredoc);
	restore_fd(preserve_fd[1], STDOUT_FD);
	redirect_fd(&preserve_fd[0], STDIN_FD, pipe_fd[0]);
	ldpre_ast(ast->right, env, exec, heredoc);
	restore_fd(preserve_fd[0], STDIN_FD);
	return (0);
}
