/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:01 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/12 22:19:03 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	*make_prompt_f(void);
char		*input_readline_f(void);

/*
char	*input_readline_f(void)
:return: string containg user's input.

Weeklyshell's input module wrapper function. Prompts interactive shell
and returns user's input. Uses GNU readline library functions to perform
actions, and uses history library to save inputs.

It's caller's responsibility to free the returned pointer after use.
*/
char	*input_readline_f(void)
{
	char				*input;
	char				*prompt;
	struct sigaction	oldacts[2];
	struct termios		oldterm;

	prompt = make_prompt_f();
	input_sighandler_setup(oldacts);
	input_terminal_setup(&oldterm);
	input = readline(prompt);
	input_sighandler_restore(oldacts);
	input_terminal_restore(&oldterm);
	if (input != NULL && *input != '\0')
		add_history(input);
	free(prompt);
	return (input);
}

/*
static char	*make_prompt_f(void)
:return: string containg prompt string.

Makes shell prompt containing Current Working Directory (CWD). 
It's caller's responsibility to free the returned pointer after use.
*/
static char	*make_prompt_f(void)
{
	char	*ret;
	char	*temp;
	char	*temp2;

	temp = strdup(TERM_COLOR_GREEN "weeklyshell"
			TERM_COLOR_END ":" TERM_COLOR_YELLOW);
	temp2 = getcwd(NULL, 0);
	ret = malloc(strlen(temp) + strlen(temp2) + 6 + 1);
	if (ret == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	strncpy(ret, temp, strlen(temp) + 1);
	strncat(ret, temp2, strlen(ret) + strlen(temp2) + 1);
	strncat(ret, TERM_COLOR_END "$ ", strlen(ret) + 6 + 1);
	free(temp);
	free(temp2);
	return (ret);
}
