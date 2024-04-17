/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:00 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/17 14:29:12 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

int	ldpre_ast_subshell(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

/*
Note that on successful execution, the `return (-1)` expression
won't be called, as do_exit function is a wrapper for exit(2) call.
But compiler does not understand out custom wrapper, so i put an
additional line here :(
*/
int	ldpre_ast_subshell(t_ast_node *ast, t_ld_map_env *env,
		t_ld_exec_nodes *exec, t_ld_heredoc *heredoc)
{
	pid_t	pid;
	int		exitcode;

	if (env->should_postpone)
		return (-1);
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
	return (-1);
}
