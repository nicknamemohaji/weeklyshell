/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:11:55 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 05:27:22 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

int				ldexec_run_bin(t_ld_struct_exec exec);
t_bool			ldexec_redir(t_ld_array_redir redir,
					t_ld_array_pipe pipe, char *heredoc_tmpfile);
static void		redir_pipe(t_ld_array_pipe pipe);
static t_bool	redir_redir_stdin(t_ld_redir_node *node, char *heredoc_tmpfile);
static t_bool	redir_redir_stdout(t_ld_redir_node *node);

int	ldexec_run_bin(t_ld_struct_exec exec)
{
	// TODO child 프로세스 관련 부분을 별도 함수로 분리
	// TODO builtin 실행
	// TODO 실행 이후 환경 정리
	// - exec.envp, exec.argv, exec.redir.stdin/out, pipe (if set))
	// - env에 exitcode 업로드
	pid_t				pid;
	char				*heredoc_tmpfile;
	struct sigaction	oldacts[2];

	heredoc_tmpfile = ldexec_heredoc_assign_f();
	/*
	if (exec.path == NULL)
		return (builtin_wrapper(exec));
	*/
	pid = fork();
	if (pid < 0)
		do_exit("ldexec_run_bin.fork");
	else if (pid == 0)
	{
		if (ldexec_redir(exec.redir, exec.pipe, heredoc_tmpfile) == FALSE)
			exit(EXIT_FAILURE);
		if (execve(exec.path, exec.argv, exec.envp) < 0)
			do_exit("ldexec_run_bin.execve");
	}
	close(exec.pipe.stdin);
	close(exec.pipe.stdout);
	ldexec_sigign_setup(oldacts);
	if (wait(&pid) < 0)
		do_exit("ldexec_run_bin.wait");
	input_sighandler_restore(oldacts);
	unlink(heredoc_tmpfile);
	free(heredoc_tmpfile);
	return (pid);
}

t_bool	ldexec_redir(t_ld_array_redir redir,
					t_ld_array_pipe pipe, char *heredoc_tmpfile)
{
	if (redir_redir_stdin(redir.stdin, heredoc_tmpfile) == FALSE)
		return (FALSE);
	if (redir_redir_stdout(redir.stdout) == FALSE)
		return (FALSE);
	redir_pipe(pipe);
	return (TRUE);
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

static t_bool	redir_redir_stdin(t_ld_redir_node *node, char *heredoc_tmpfile)
{
	int		fd;

	while (node != NULL)
	{
		if (node->mode == IN_HEREDOC)
		{
			if (heredoc_tmpfile != NULL)
				fd = open(heredoc_tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = -1;
			if (ldexec_heredoc(fd, node->filename) == FALSE)
				return (FALSE);
			node->filename = heredoc_tmpfile;
			close(fd);
		}
		if (close(STDIN_FD) != 0)
			do_exit("ldexec_run.redir_redir_stdin.close");
		if (open(node->filename, O_RDONLY) < 0)
		{
			ld_errno_file("ldexec_run.redir_redir_stdin.open", node->filename);
			return (FALSE);
		}
		node = node->next;
	}
	return (TRUE);
}

static t_bool	redir_redir_stdout(t_ld_redir_node *node)
{
	while (node != NULL)
	{
		if (close(STDOUT_FD) != 0)
			do_exit("ldexec_run.redir_redir_stdout.close");
		if (open(node->filename, O_WRONLY | O_CREAT | node->mode, 0644) < 0)
		{
			ld_errno_file("ldexec_run.redir_redir_stdout.open", node->filename);
			return (FALSE);
		}
		node = node->next;
	}
	return (TRUE);
}
