/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:20:45 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/04 17:05:36 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "parser.h"
#include "types.h"
#include "utils.h"

static t_bool open_outfile(char *filename, enum e_node_type mode)
{
	int	fd;

	if (access(filename, F_OK) && access(filename, F_OK | W_OK) != 0)
		return (ld_errno_file("ldpre_ast.open_outfile.access", filename));
	close(STDOUT_FD);
	if (mode == EXP_PRE_RWRITE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ld_errno_file("ldpre_ast.open_outfile.open", filename));
	return (TRUE);
}

static t_bool open_infile(char *filename, char *heredoc_name, enum e_node_type mode)
{
	int		fd;
	t_bool	res;

	if (mode == EXP_PRE_RHEREDOC && access(heredoc_name, F_OK | W_OK | R_OK) != 0)
		return (ld_errno_file("ldpre_ast.open_outfile.access", heredoc_name));
	if (mode == EXP_PRE_RREAD && access(filename, F_OK) && access(filename, F_OK | R_OK) != 0)
		return (ld_errno_file("ldpre_ast.open_infile.access", filename));
	res = TRUE;
	close(STDIN_FD);
	if (mode == EXP_PRE_RREAD)
		fd = open(filename, O_RDONLY);
	else
	{
		fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			do_exit("ldpre_ast.open_infile.open");
		res = ldexec_heredoc(fd, filename);
		close(fd);
		fd = open(heredoc_name, O_RDONLY);
	}
	if (fd < 0)
		return (ld_errno_file("ldpre_ast.open_infile.open", filename));
	return (res);
}

int	ldpre_ast(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, char *heredoc_name)
{
	switch(ast->node_type)
	{
		case NODE_COMMAND:
			{
				t_ld_exec_nodes	*node;
				t_bool			free_flag;
				
				node = malloc(1 * sizeof(t_ld_exec_nodes));
				if (node == NULL)
					do_exit("ldpre_ast.malloc");
				node->next = NULL;
				(node->exec).argv = ldpre_param_wrapper_f(ast->pcmd, env);
				(node->exec).envp = ldpre_env_toenvp_f(env);
				(node->exec).path = ldexec_exec_find_f(
						(node->exec).argv[0], &free_flag, ldpre_env_fetch("PATH", env));
				ldexec_select_type(node->exec, node, env);
				if (free_flag)
					free((node->exec).path);	
				if (exec == NULL)
					return (exec_cleanup(node, env));
				else
				{
					while (exec->next != NULL)
						exec = exec->next;
					exec->next = node;
					return (-1);
				}
			}
			break;
		

		case EXP_SUBSHELL:
			{
				pid_t	pid;
				int		exitcode;
				pid = fork();
				if (pid < 0)
					do_exit("ldpre_ast.fork");
				else if (pid == 0)
					exit(ldpre_ast(ast->left, env, exec, heredoc_name));
				else
				{
					if (waitpid(pid, &exitcode, 0) < 0)
						do_exit("ldpre_ast.waitpid");
					return (exitcode);
				}
			}
			break;
		case EXP_IN_PIPE:
			{
				t_ld_exec_nodes	start;
				int				stdin_fd;
				int				stdout_fd;
				int				fd[2];

				start.next = NULL;
				// TODO make pipe subshell

				// prepare pipe
				if (pipe(fd) < 0)
					do_exit("ldpre_ast.pipe");
				
				// redirect stdout to pipe
				stdout_fd = dup(STDOUT_FD);
				if (stdout_fd < 0)
					do_exit("ldpre_ast.dup");
				close(STDOUT_FD);
				if (dup(fd[1]) < 0)
					do_exit("ldpre_ast.dup");
				close(fd[1]);
				// run
				if (exec == NULL)
					ldpre_ast(ast->left, env, &start, heredoc_name);
				else
					ldpre_ast(ast->left, env, exec, heredoc_name);
				// restore stdout
				close(STDOUT_FD);
				if (dup(stdout_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdout_fd);

				// redirect stdin to pipe
				stdin_fd = dup(STDIN_FD);
				if (stdin_fd < 0)
					do_exit("ldpre_ast.dup");
				close(STDIN_FD);
				if (dup(fd[0]) < 0)
					do_exit("ldpre_ast.dup");
				close(fd[0]);
				// run
				if (exec == NULL)
					ldpre_ast(ast->right, env, &start, heredoc_name);
				else
					ldpre_ast(ast->right, env, exec, heredoc_name);
				// restore stdin
				close(STDIN_FD);
				if (dup(stdin_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdin_fd);

				// cleanup
				if (exec == NULL)
				{
					exec_cleanup(start.next, env);
					return (0);
				}
				return (-1);
			}
			break;
		
		case EXP_IN_AND:
			{
				int	exitcode;
				int	stdin_fd;
				int	stdout_fd;
				// save stdin and stdout
				stdin_fd = dup(STDIN_FD);
				if (stdin_fd < 0)
					do_exit("ldpre_ast.dup");
				stdout_fd = dup(STDOUT_FD);
				if (stdout_fd < 0)
					do_exit("ldpre_ast.dup");

				// run
				exitcode = ldpre_ast(ast->left, env, exec, heredoc_name);
				if (exitcode == 0)
					exitcode = ldpre_ast(ast->right, env, exec, heredoc_name);
				
				// restore fds
				close(STDIN_FD);
				if (dup(stdin_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdin_fd);
				close(STDOUT_FD);
				if (dup(stdout_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdout_fd);
				return (exitcode);
			}
			break;
		case EXP_IN_OR:
			{
				int	exitcode;
				int	stdin_fd;
				int	stdout_fd;
				// save stdin and stdout
				stdin_fd = dup(STDIN_FD);
				if (stdin_fd < 0)
					do_exit("ldpre_ast.dup");
				stdout_fd = dup(STDOUT_FD);
				if (stdout_fd < 0)
					do_exit("ldpre_ast.dup");

				// run
				exitcode = ldpre_ast(ast->left, env, exec, heredoc_name);
				if (exitcode != 0)
					exitcode = ldpre_ast(ast->right, env, exec, heredoc_name);
				
				// restore fds
				close(STDIN_FD);
				if (dup(stdin_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdin_fd);
				close(STDOUT_FD);
				if (dup(stdout_fd) < 0)
					do_exit("ldpre_ast.dup");
				close(stdout_fd);
				return (exitcode);
			}
			break;
		
		case EXP_IN_RAPPEND:	// FALLTHROUGH
		case EXP_IN_RWRITE:
			{
				if ((ast->left)->node_type == NODE_FILE)
				{
					// open left
					open_outfile((ast->left)->pcmd[0], ast->node_type);
					// open right
					if ((ast->right)->node_type == NODE_FILE)
						open_outfile((ast->right)->pcmd[0], ast->node_type);
					else
						ldpre_ast(ast->right, env, exec, heredoc_name);
				}
				else
				{
					// open right
					if ((ast->right)->node_type == NODE_FILE)
						open_outfile((ast->right)->pcmd[0], ast->node_type);
					else
						ldpre_ast(ast->right, env, exec, heredoc_name);
					return (ldpre_ast(ast->left, env, exec, heredoc_name));
				}
				return -1;
			}
			break;
		
		case EXP_PRE_RREAD:		// FALLTHROUGH
		case EXP_PRE_RHEREDOC:
			{
				// TODO command가 없는 경우
				if ((ast->right)->node_type == NODE_FILE)
				{
					// open right
					open_infile((ast->right)->pcmd[0], heredoc_name, ast->node_type);
					// open left 
					if ((ast->left)->node_type == NODE_FILE)
						open_infile((ast->left)->pcmd[0], heredoc_name, ast->node_type);
					else
						ldpre_ast(ast->left, env, exec, heredoc_name);
				}
				else
				{
					// open left
					if ((ast->left)->node_type == NODE_FILE)
						open_infile((ast->left)->pcmd[0], heredoc_name, ast->node_type);
					else
						ldpre_ast(ast->left, env, exec, heredoc_name);
					return (ldpre_ast(ast->right, env, exec, heredoc_name));
				}
				return -1;		
			}
			break;
		
		case EXP_PRE_RAPPEND:
		case EXP_PRE_RWRITE:
			{
				// TODO command가 없는 경우
			}
			break;
		default:
			break;
	}
	return (-2);
}
