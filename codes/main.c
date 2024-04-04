/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/01 13:03:53 by nicknamemoh      ###   ########.fr       */
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
	while (1)
	{
		input = input_readline_f();
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
