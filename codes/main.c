/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/27 07:01:47 by nicknamemoh      ###   ########.fr       */
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
	t_bool wildcard;
	str = ldpre_param_quote_f(strdup(TEST1), env, &wildcard);
	printf("quote (" TEST1 ") ----> (%s)\n", str);
	free(str);
	# define TEST2 "\'$TESTARG...$TE??$...\"\'"
	str = ldpre_param_expansion_f(strdup(TEST2), env);
	printf("exapnsion (" TEST2 ") ----> (%s)\n", str);
	free(str);
	str = ldpre_param_quote_f(strdup(TEST2), env, &wildcard);
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
	# define TEST5 "\'\'*\"t\""
	str = ldpre_param_quote_f(strdup(TEST5), env, &wildcard);
	printf("exapnsion (" TEST5 ") ----> (%s)\n", str);
	printf("wait... wildcard %d\n", wildcard);
	if (wildcard)
	{
		strs = ldpre_param_wildcard_f(str);
		for (int i = 0; strs[i] != NULL; i++)
			printf("%d: %s\n", i, strs[i]);
		free_ft_split(strs);
	}
	else
		free(str);
	# define TEST6 "\'*\'\"t\""
	str = ldpre_param_quote_f(strdup(TEST6), env, &wildcard);
	printf("exapnsion (" TEST6 ") ----> (%s)\n", str);
	printf("wait... wildcard %d\n", wildcard);
	if (wildcard)
	{
		strs = ldpre_param_wildcard_f(str);
		for (int i = 0; strs[i] != NULL; i++)
			printf("%d: %s\n", i, strs[i]);
		free_ft_split(strs);
	}
	else
		free(str);

	// TEST exec
	t_bool need_free;
	char** __envp = ldpre_env_toenvp_f(env);
	printf("pid %d path (%s)\n", getpid(), ldpre_env_fetch("PATH", env));
	t_ld_struct_exec exec = {
		.path = ldexec_exec_find_f("cat", &need_free, ldpre_env_fetch("PATH", env)),
		.argv = (char *[]){"cat", "-", "main.c", NULL},
		.envp = __envp,
		.pipe = (t_ld_array_pipe){-1, -1},
		.redir = (t_ld_array_redir){
			.stdin = &(t_ld_redir_node){
				.filename = "HERE",
				.mode = IN_HEREDOC
			},
			.stdout = NULL
		}
	};
	printf("pid %d exitcode: %d\n", getpid(), ldexec_run_bin(exec));
	printf("path %s need_free %d\n", exec.path, need_free);
	if (need_free == TRUE)
		free(exec.path);
	free_ft_split(__envp);

	// TEST builtin
	exec.redir = (t_ld_array_redir){NULL, NULL};
	exec.argv = (char *[]){"echo", "hello", "world", NULL};
	printf("pid %d exitcode: %d\n", getpid(), builtin_wrapper(exec, env));
	
	while (1)
	{
		input = input_readline_f();
		if (input == NULL)
			break ;
		if (input_validate(input) == TRUE)
		{
			if (ft_strlen(input) == 0)
				continue ;
			// loader_wrapper(input, env);			
			// TEST
			printf("input %p\n", input);
			char **args = ft_split(input, ' ');
			for (int i = 0; args[i] != NULL; i++)
			{
				args[i] = ldpre_param_quote_f(args[i], env, &wildcard);
				if (wildcard)
					printf("YO DO WILDCARD");
			}
			exec.argv = args;
			if (builtin_isbuiltin(exec.argv[0]))
				printf("pid %d exitcode: %d\n", getpid(), builtin_wrapper(exec, env));
			else
			{
				exec.envp = ldpre_env_toenvp_f(env);
				exec.path = ldexec_exec_find_f(exec.argv[0], &need_free, ldpre_env_fetch("PATH", env));
				if (exec.path == NULL)
				{
					printf("command not found\n");
					ldexec_env_exitcode_update(127, env);
				}
				else
				{					
					printf("path %s\n", exec.path);
					for (int i = 0; exec.argv[i] != NULL; i++)
						printf("argv[%d]: %s\n", i, exec.argv[i]);
					ldexec_env_exitcode_update(ldexec_run_bin(exec), env);
				}
				free_ft_split(exec.envp);
				if (need_free == TRUE)
					free(exec.path);
			}
			free_ft_split(args);
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
