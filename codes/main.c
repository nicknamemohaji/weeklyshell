/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:43 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/12 22:17:54 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	// t_ld_map_env	env;
	char			*input;

	(void)argc;
	(void)argv;
	(void)envp;
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
	free(input);
	rl_clear_history();
	return (0);
}
