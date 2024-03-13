/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/14 02:43:07 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int				ldexec_run(t_ld_struct_exec exec);
static void		redir_pipe(t_ld_array_pipe pipe);
static t_bool	redir_redir(t_ld_array_redir redir);
static t_bool	redir_redir_stdin(t_ld_redir_node *node);
static t_bool	redir_redir_stdout(t_ld_redir_node *node);

int	ldexec_run(t_ld_struct_exec exec)
{
	// TODO
	// 1. match norm
	// 2. add comments on functions
	// 3. unlink temporary heredoc files
	pid_t	pid;
	int		exitcode;

	pid = fork();
	if (pid < 0)
		do_exit("ldexec_run.fork");
	else if (pid == 0)
	{
		redir_pipe(exec.pipe);
		if (redir_redir(exec.redir) == FALSE)
			return (127);
		pid = execve(exec.path, exec.argv, exec.envp);
		if (pid < 0)
			do_exit("ldexec_run.execve");
	}
	if (exec.pipe.stdin != -1)
		close(exec.pipe.stdin);
	if (exec.pipe.stdout != -1)
		close(exec.pipe.stdout);
	pid = wait(&exitcode);
	if (pid < 0)
		do_exit("ldexec_run.wait");
	return (exitcode);
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

static t_bool	redir_redir(t_ld_array_redir redir)
{
	if (redir_redir_stdin(redir.stdin) == FALSE)
		return (FALSE);
	if (redir_redir_stdout(redir.stdout) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	redir_redir_stdin(t_ld_redir_node *node)
{
	int		fd;

	while (node != NULL)
	{
		if (node->mode == IN_HEREDOC)
		{
			fd = ldexec_heredoc_tmpfile();
			if (ldexec_heredoc(fd, node->filename) == FALSE)
				return (FALSE);
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
}