/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:16:24 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/04 16:42:12 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "minishell.h"
#include "types.h"
#include "utils.h"
#include "parser.h"

void		loader_wrapper(char *input, t_ld_map_env *env);
static void	fd_preserve(int *stdin_fd, int *stdout_fd);
static void	fd_restore(int stdin_fd, int stdout_fd);

void	loader_wrapper(char *input, t_ld_map_env *env)
{
	int					stdin_fd;
	int					stdout_fd;
	struct sigaction	oldacts[2];
	t_ast_node			*ast;
	char				*heredoc_name;

	fd_preserve(&stdin_fd, &stdout_fd);
	ldexec_sigign_setup(oldacts);
	heredoc_name = ldexec_heredoc_assign_f();
	if (heredoc_name == NULL)
	{
		printf("cannot open heredoc :tried %d times :(\n", HEREDOC_MAX);
		return ;
	}
	ast = parse_f(input);
	if (ast != NULL)
		ldpre_ast(ast, env, NULL, heredoc_name);
	fd_restore(stdin_fd, stdout_fd);
	input_sighandler_restore(oldacts);
	delete_ast_node(ast);
	unlink(heredoc_name);
	free(heredoc_name);
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
		if (close(STDOUT_FD) != 0)
			do_exit("loader_wrapper.fd_restore.close");
		if (dup2(stdout_fd, STDOUT_FD) < 0)
			do_exit("loader_wrapper.fd_restore.dup2");
		if (close(stdout_fd) != 0)
			do_exit("loader_wrapper.fd_restore.close");
	}
	if (stdin_fd != -1)
	{
		if (close(STDIN_FD) != 0)
			do_exit("loader_wrapper.fd_restore.close");
		if (dup2(stdin_fd, STDIN_FD) < 0)
			do_exit("loader_wrapper.fd_restore.dup2");
		if (close(stdin_fd) != 0)
			do_exit("loader_wrapper.fd_restore.close");
	}
}
