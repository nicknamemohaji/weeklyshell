/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:08:58 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/08 18:49:04 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int			ldpre_ast_pipe(t_ast_node *ast, t_ld_map_env *env,
				t_ld_exec_nodes *exec, t_ld_heredoc heredoc);
static void	redirect_fd(int *fd_preserve, int fd_target, int fd_redirect);
static void	restore_fd(int fd_preserve, int fd_target);


int	ldpre_ast_pipe(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc heredoc)
{
	t_ld_exec_nodes	start;
	int				preserve_fd[2];
	int				pipe_fd[2];

	// TODO 서브트리 상태 대응
	start.next = NULL;
	if (pipe(pipe_fd) < 0)
		do_exit("ldpre_ast_pipe.pipe");
	redirect_fd(&preserve_fd[1], STDOUT_FD, pipe_fd[1]);
	if (exec == NULL)
		ldpre_ast(ast->left, env, &start, heredoc);
	else
		ldpre_ast(ast->left, env, exec, heredoc);
	restore_fd(preserve_fd[1], STDOUT_FD);
	redirect_fd(&preserve_fd[0], STDIN_FD, pipe_fd[0]);
	if (exec == NULL)
		ldpre_ast(ast->right, env, &start, heredoc);
	else
		ldpre_ast(ast->right, env, exec, heredoc);
	restore_fd(preserve_fd[0], STDIN_FD);
	if (exec == NULL)
	{
		exec_cleanup(start.next, env, FALSE);
		return (0);
	}
	return (-1);
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
