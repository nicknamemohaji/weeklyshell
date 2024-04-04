/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:20:45 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/04 19:14:32 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "parser.h"
#include "types.h"
#include "utils.h"


int	ldpre_ast(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc heredoc)
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
					exit(ldpre_ast(ast->left, env, exec, heredoc));
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
				// TODO make pipe subshell (`exit 1 | unset A | export A=1 | echo $A`)

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
					ldpre_ast(ast->left, env, &start, heredoc);
				else
					ldpre_ast(ast->left, env, exec, heredoc);
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
					ldpre_ast(ast->right, env, &start, heredoc);
				else
					ldpre_ast(ast->right, env, exec, heredoc);
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
				exitcode = ldpre_ast(ast->left, env, exec, heredoc);
				if (exitcode == 0)
					exitcode = ldpre_ast(ast->right, env, exec, heredoc);
				
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
				exitcode = ldpre_ast(ast->left, env, exec, heredoc);
				if (exitcode != 0)
					exitcode = ldpre_ast(ast->right, env, exec, heredoc);
				
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
					if (ldpre_ast_redir_outfile((ast->left)->pcmd[0], ast->node_type) == FALSE)
						return (-2);
					// open right
					if ((ast->right)->node_type == NODE_FILE)
					{
						if (ldpre_ast_redir_outfile((ast->right)->pcmd[0], ast->node_type) == FALSE)
							return (-2);
					}
					else if (ldpre_ast(ast->right, env, exec, heredoc) < 0)
						return (-2);
				}
				else
				{
					// open right
					if ((ast->right)->node_type == NODE_FILE)
					{
						if (ldpre_ast_redir_outfile((ast->right)->pcmd[0], ast->node_type) == FALSE)
							return (-2);
					}
					else if (ldpre_ast(ast->right, env, exec, heredoc) < 0)
						return (-2);
					return (ldpre_ast(ast->left, env, exec, heredoc));
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
					ldpre_ast_redir_infile((ast->right)->pcmd[0], heredoc, ast->node_type, env);
					// open left 
					if ((ast->left)->node_type == NODE_FILE)
						ldpre_ast_redir_infile((ast->left)->pcmd[0], heredoc, ast->node_type, env);
					else
						ldpre_ast(ast->left, env, exec, heredoc);
				}
				else
				{
					// open left
					if ((ast->left)->node_type == NODE_FILE)
						ldpre_ast_redir_infile((ast->left)->pcmd[0], heredoc, ast->node_type, env);
					else
						ldpre_ast(ast->left, env, exec, heredoc);
					return (ldpre_ast(ast->right, env, exec, heredoc));
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