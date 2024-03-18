/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/19 02:27:25 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint = FALSE;

int	main(int argc, char *argv[], char *envp[])
{
	t_ld_map_env	*env;
	char			*input;

	(void)argc;
	(void)argv;
	env = ldpre_env_fromenvp_f(envp);

	// TEST
	printf("PATH before: %s\n", ldpre_env_fetch("PATH", env));
	ldpre_env_add(strdup("PATH"), strdup("/"), env);
	printf("PATH after modi: %s\n", ldpre_env_fetch("PATH", env));
	ldpre_env_remove("PATH", env);
	printf("PATH after delete: %s\n", ldpre_env_fetch("PATH", env));

	// TEST
	printf("pid %d\n", getpid());
	t_ld_struct_exec exec = {
		.path = "/bin/cat",
		.argv = (char *[]){"cat", "-", "Makefile", NULL},
		.envp = ldpre_env_toenvp_f(env),
		.pipe = (t_ld_array_pipe){-1, -1},
		.redir = (t_ld_array_redir){
			.stdin = &(t_ld_redir_node){
				.filename = "HERE",
				.mode = IN_HEREDOC
			},
			.stdout = NULL
		}
	};
	printf("pid %d exitcode: %d\n", getpid(), ldexec_run(exec));
	
	// env = ldpre_env_load(envp);
	while (1)
	{
		input = input_readline_f();
		if (input == NULL)
			break ;
		if (input_validate(input) == TRUE)
		{
			// loader_wrapper(input, env);
			printf("input: %s\n", input);
		}
		else
			printf(TERM_COLOR_RED "Syntax Error" TERM_COLOR_END "\n");
		free(input);
	}
	free_ld_map(env);
	free(input);
	rl_clear_history();
	return (0);
}
