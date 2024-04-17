/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:16:24 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/17 15:06:29 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "minishell.h"
#include "types.h"
#include "utils.h"
#include "parser.h"

static	t_bool	init_heredoc_f(t_ld_heredoc *self, int infd, int outfd);
static void		clean_heredoc(t_ld_heredoc *self);
void			loader_wrapper(char *input, t_ld_map_env *env);
static void		fd_preserve(int *stdin_fd, int *stdout_fd);
static void		fd_restore(int stdin_fd, int stdout_fd);

/*
	initialize object 't_ld_heredoc'.

	construct vector of char *, vector of heredoc file's name.
	set in and out fd of tty
*/
static	t_bool	init_heredoc_f(t_ld_heredoc *self, int infd, int outfd)
{
	self->phd_name_vec = new_ftvec(construct_heredoc_name,
			destruct_heredoc_name, sizeof(char *));
	if (self->phd_name_vec == NULL)
		return (FALSE);
	self->stdin_fd = infd;
	self->stdout_fd = outfd;
	return (TRUE);
}

/*
	clean content of object 't_ld_heredoc'

	unlink all the heredoc file using name of the heredoc.
	all the name of the heredoc file is in phd_name_vec.

	delete phd_name_vec.
*/
static void	clean_heredoc(t_ld_heredoc *self)
{
	const char	**hhdoc_name_vec = self->phd_name_vec->pbuffer;
	size_t		idx;

	idx = -1;
	while (++idx < self->phd_name_vec->size)
	{
		unlink((const char *)hhdoc_name_vec[idx]);
	}
	delete_ftvec(self->phd_name_vec);
	self->phd_name_vec = NULL;
}

void	loader_wrapper(char *input, t_ld_map_env *env)
{
	int					stdin_fd;
	int					stdout_fd;
	struct sigaction	oldacts[2];
	t_ast_node			*ast;
	t_ld_heredoc		heredoc;

	env->should_postpone = FALSE;
	fd_preserve(&stdin_fd, &stdout_fd);
	ldexec_signal_setup(oldacts);
	if (!init_heredoc_f(&heredoc, stdin_fd, stdout_fd))
	{
		printf("cannot open heredoc :tried %d times :(\n", HEREDOC_MAX);
		return ;
	}
	ast = parse_f(input);
	if (ast != NULL)
		ldpre_ast(ast, env, NULL, &heredoc);
	fd_restore(stdin_fd, stdout_fd);
	input_sighandler_restore(oldacts);
	delete_ast_node(ast);
	clean_heredoc(&heredoc);
}

static void	fd_preserve(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FD);
	if (*stdin_fd < 0)
		do_exit("loader_wrapper.fd_preserve.dup");
	*stdout_fd = dup(STDOUT_FD);
	if (*stdout_fd < 0)
		do_exit("loader_wrapper.fd_preserve.dup");
}

static void	fd_restore(int stdin_fd, int stdout_fd)
{
	if (stdout_fd != -1)
	{
		close(STDOUT_FD);
		if (dup2(stdout_fd, STDOUT_FD) < 0)
			do_exit("loader_wrapper.fd_restore.dup2");
		close(stdout_fd);
	}
	if (stdin_fd != -1)
	{
		close(STDIN_FD);
		if (dup2(stdin_fd, STDIN_FD) < 0)
			do_exit("loader_wrapper.fd_restore.dup2");
		close(stdin_fd);
	}
}
