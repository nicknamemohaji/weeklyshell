/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:20:45 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/08 19:20:37 by kyungjle         ###   ########.fr       */
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
				// TODO stdin에서 입력받는 커맨드들이 이상하게 실행
				t_ld_exec_nodes	*node;
				t_bool			free_flag;
				pid_t			pid;
				int				exitcode;

				// 1. 실행정보 기입				
				node = malloc(1 * sizeof(t_ld_exec_nodes));
				if (node == NULL)
					do_exit("ldpre_ast.malloc");
				node->next = NULL;
				(node->exec).argv = ldpre_param_wrapper_f(ast->pcmd, env);
				(node->exec).envp = ldpre_env_toenvp_f(env);
				(node->exec).path = ldexec_exec_find_f(
						(node->exec).argv[0], &free_flag, ldpre_env_fetch("PATH", env));

				// 2. 실행
				// 2-1. 파이프이면 fork				
				if (exec != NULL)
				{
					pid = fork();
					if (pid < 0)
						do_exit("ldpre_ast.fork");
				}
				else
					pid = -1;
				// 2-2. !PIPE || (PIPE && CHILD)
				if (pid <= 0)
				{
					ldexec_select_type(node->exec, node, env, pid);
					exitcode = exec_cleanup(node, env, free_flag);
				}
				// PIPE && !CHILD
				else
				{
					node->pid = pid;
					while (exec->next != NULL)
						exec = exec->next;
					exec->next = node;
					return (-1);
				}

				// 3. 종료
				// (단일 커맨드면 exec_cleanup에서 정리됨 / 자식 프로세스는 종료됨 / 파이프면 한 번에 정리함)
				if (pid == 0)
					exit(exitcode);
				return (exitcode);
			}
			break;

		case EXP_SUBSHELL:
			{
				return (ldpre_ast_subshell(ast, env, exec, heredoc));
			}
			break;
		case EXP_IN_PIPE:
			{
				return (ldpre_ast_pipe(ast, env, exec, heredoc));
			}
			break;
		
		case EXP_IN_AND:
			{
				return (ldpre_ast_and(ast, env, exec, heredoc));
			}
			break;
		case EXP_IN_OR:
			{
				return (ldpre_ast_or(ast, env, exec, heredoc));
			}
			break;
		
		case EXP_IN_RAPPEND:	// FALLTHROUGH
		case EXP_IN_RWRITE:
			{
				return (ldpre_ast_wopen(ast, env, exec, heredoc));
			}
			break;
		
		case EXP_PRE_RREAD:		// FALLTHROUGH
		case EXP_PRE_RHEREDOC:
			{
				return (ldpre_ast_ropen(ast, env, exec, heredoc));
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
