/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/18 19:22:31 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

int				ldexec_run(t_ld_struct_exec exec);
static void		redir_pipe(t_ld_array_pipe pipe);
static t_bool	redir_redir(t_ld_array_redir redir,
					t_ld_array_pipe pipe, char *heredoc_tmpfile);
static t_bool	redir_redir_stdin(t_ld_redir_node *node, char *heredoc_tmpfile);
static t_bool	redir_redir_stdout(t_ld_redir_node *node);

int	ldexec_run(t_ld_struct_exec exec)
{
	pid_t				pid;
	char				*heredoc_tmpfile;
	struct sigaction	oldacts[2];

	heredoc_tmpfile = ldexec_heredoc_assign();
	input_sigign_setup(oldacts);
	pid = fork();
	if (pid < 0)
		do_exit("ldexec_run.fork");
	else if (pid == 0)
	{
		if (redir_redir(exec.redir, exec.pipe, heredoc_tmpfile) == FALSE)
			exit(EXIT_FAILURE);
		if (execve(exec.path, exec.argv, exec.envp) < 0)
			do_exit("ldexec_run.execve");
	}
	close(exec.pipe.stdin);
	close(exec.pipe.stdout);
	if (wait(&pid) < 0)
		do_exit("ldexec_run.wait");
	unlink(heredoc_tmpfile);
	free(heredoc_tmpfile);
	input_sighandler_restore(oldacts);
	return (pid);
}

static void	redir_pipe(t_ld_array_pipe pipe)
{
	if (pipe.stdin != -1)
	{
		if (dup2(pipe.stdin, STDIN_FD) == -1)
			do_exit("ldexec_run.redir_pipe.dup2");
	}
	if (pipe.stdout != -1)
	{
		if (dup2(pipe.stdout, STDOUT_FD) == -1)
			do_exit("ldexec_run.redir_pipe.dup2");
	}
}

static t_bool	redir_redir(t_ld_array_redir redir,
					t_ld_array_pipe pipe, char *heredoc_tmpfile)
{
	if (redir_redir_stdin(redir.stdin, heredoc_tmpfile) == FALSE)
		return (FALSE);
	if (redir_redir_stdout(redir.stdout) == FALSE)
		return (FALSE);
	redir_pipe(pipe);
	return (TRUE);
}

static t_bool	redir_redir_stdin(t_ld_redir_node *node, char *heredoc_tmpfile)
{
	int		fd;

	while (node != NULL)
	{
		if (node->mode == IN_HEREDOC)
		{
			fd = open(heredoc_tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (ldexec_heredoc(fd, node->filename) == FALSE)
				return (FALSE);
			node->filename = heredoc_tmpfile;
			close(fd);
		}
		fd = open(node->filename, O_RDONLY);
		if (fd < 0)
		{
			ld_errno_file("ldexec_run.redir_redir.open", node->filename);
			return (FALSE);
		}
		if (dup2(fd, STDIN_FD) == -1)
			do_exit("ldexec_run.redir_redir.dup2");
		node = node->next;
	}
	return (TRUE);
}

static t_bool	redir_redir_stdout(t_ld_redir_node *node)
{
	int	fd;

	while (node != NULL)
	{
		fd = open(node->filename, O_WRONLY | O_CREAT | node->mode, 0644);
		if (fd < 0)
		{
			ld_errno_file("ldexec_run.redir_redir.open", node->filename);
			return (FALSE);
		}
		if (dup2(fd, STDOUT_FD) == -1)
			do_exit("ldexec_run.redir_redir.dup2");
		node = node->next;
	}
	return (TRUE);
}
