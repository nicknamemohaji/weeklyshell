/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:16:24 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/01 15:15:05 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "minishell.h"
#include "types.h"
#include "utils.h"

void		loader_wrapper(char *input, t_ld_map_env *env);
static void	fd_preserve(int *stdin_fd, int *stdout_fd);
static void	fd_restore(int stdin_fd, int stdout_fd);

void	loader_wrapper(char *input, t_ld_map_env *env)
{
	int					stdin_fd;
	int					stdout_fd;
	struct sigaction	oldacts[2];

	fd_preserve(&stdin_fd, &stdout_fd);
	ldexec_sigign_setup(oldacts);
	// TODO call parser
	
	// TEST >>
	char **argv_split = ft_split(input, ' ');
	t_ld_exec_nodes *nodes = malloc(1 * sizeof(t_ld_exec_nodes));
	nodes->exec = (t_ld_exec){
		.argv = argv_split
	};
	nodes->next = NULL;
	exec_prepare(nodes, env);
	exec_cleanup(nodes, env);
	// <<
	
	// TODO travel ast
	fd_restore(stdin_fd, stdout_fd);
	input_sighandler_restore(oldacts);
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
