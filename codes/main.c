/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/09 15:55:30 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint = FALSE;

static void	ld_env_set_exitcode(t_ld_map_env *env);

int	main(int argc, char *argv[], char *envp[])
{
	t_ld_map_env	*env;
	char			*input;

	(void)argc;
	(void)argv;
	env = ldpre_env_fromenvp_f(envp);
	ld_env_set_exitcode(env);
	while (1)
	{
		input = input_readline_f(env);
		if (input == NULL)
			break ;
		if (ft_strlen(input) != 0)
		{
			if (input_validate(input) == TRUE)
				loader_wrapper(input, env);
			else
				printf(TERM_COLOR_RED "Syntax Error" TERM_COLOR_END "\n");
		}
		free(input);
	}
	free_ld_map(env);
	free(input);
	rl_clear_history();
	return (0);
}

static void	ld_env_set_exitcode(t_ld_map_env *env)
{
	t_ld_map_node	*node;

	node = malloc(1 * sizeof(t_ld_map_node));
	if (node == NULL)
		do_exit("main.ld_env_set_exitcode.malloc");
	node->key = ft_strdup("?");
	node->value = ft_itoa(0);
	if (node->key == NULL || node->value == NULL)
		do_exit("main.ld_env_set_exitcode.malloc");
	node->next = env->contents;
	env->contents = node;
	// TODO shlvl
}
