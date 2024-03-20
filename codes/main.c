/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/21 00:26:19 by nicknamemoh      ###   ########.fr       */
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

	// TEST env
	printf("TESTARG before: %s\n", ldpre_env_fetch("TESTARG", env));
	ldpre_env_add(strdup("TESTARG"), strdup("this is testarg!"), env);
	printf("TESTARG after add: %s\n", ldpre_env_fetch("TESTARG", env));
	ldpre_env_add(strdup("TESTARG"), strdup("this was testarg!"), env);
	printf("TESTARG after modi: %s\n", ldpre_env_fetch("TESTARG", env));
	ldpre_env_remove("TESTARG", env);
	printf("TESTARG after delete: %s\n", ldpre_env_fetch("TESTARG", env));
	ldpre_env_add(strdup("TESTARG"), strdup("this is testarg!"), env);
	printf("TESTARG after add: %s\n", ldpre_env_fetch("TESTARG", env));

	// TEST expansion
	char *str;
	# define TEST1 "\"$TESTARG...$TE??$...\'\""
	str = ldpre_param_expansion_f(strdup(TEST1), env);
	printf("exapansion (" TEST1 ") ----> (%s)\n", str);
	free(str);
	str = ldpre_param_quote_f(strdup(TEST1), env);
	printf("quote (" TEST1 ") ----> (%s)\n", str);
	free(str);
	# define TEST2 "\'$TESTARG...$TE??$...\"\'"
	str = ldpre_param_expansion_f(strdup(TEST2), env);
	printf("exapnsion (" TEST2 ") ----> (%s)\n", str);
	free(str);
	str = ldpre_param_quote_f(strdup(TEST2), env);
	printf("quote (" TEST2 ") ----> (%s)\n", str);
	free(str);
	# define TEST3 "*"
	char **strs = ldpre_param_wildcard_f(strdup(TEST3));
	printf("(" TEST3 ") ----> \n");
	for (int i = 0; strs[i] != NULL; i++)
		printf("%d: %s\n", i, strs[i]);
	free_ft_split(strs);
	# define TEST4 "m*i*c"
	strs = ldpre_param_wildcard_f(strdup(TEST4));
	printf("(" TEST4 ") ----> \n");
	for (int i = 0; strs[i] != NULL; i++)
		printf("%d: %s\n", i, strs[i]);
	free_ft_split(strs);

	// TEST exec
	t_bool need_free;
	printf("pid %d path (%s)\n", getpid(), ldpre_env_fetch("PATH", env));
	t_ld_struct_exec exec = {
		.path = ldexec_exec_find_f("cat", &need_free, ldpre_env_fetch("PATH", env)),
		.argv = (char *[]){"cat", "-", "main.c", NULL},
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
	printf("path %s need_free %d\n", exec.path, need_free);
	if (need_free == TRUE)
		free(exec.path);
	
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
