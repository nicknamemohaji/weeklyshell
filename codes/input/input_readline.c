/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:01 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/28 02:09:10 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

static char	*make_prompt_f(void);
char		*input_readline_f(void);

/*
char	*input_readline_f(void)
:return: string containg user's input.

Weeklyshell's input module wrapper function. Prompts interactive shell
and returns user's input. Uses GNU readline library functions to perform
actions, and uses history library to save inputs.

Caller should free the returned pointer after use.
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
*/
static char	*make_prompt_f(void)
{
	char	*ret;
	char	*prompt_base;
	char	*cwd;

	prompt_base = ft_strdup(TERM_COLOR_GREEN "weeklyshell"
			TERM_COLOR_END ":" TERM_COLOR_YELLOW);
	if (prompt_base == NULL)
		do_exit("make_prompt_f.malloc");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		do_exit("make_prompt_f.getcwd");
	ret = malloc(ft_strlen(prompt_base) + ft_strlen(cwd) + 7 + 1);
	if (ret == NULL)
		do_exit("make_prompt_f.malloc");
	ft_strlcpy(ret, prompt_base, ft_strlen(prompt_base) + 1);
	ft_strlcat(ret, cwd, ft_strlen(ret) + ft_strlen(cwd) + 1);
	ft_strlcat(ret, TERM_COLOR_END "$ ", ft_strlen(ret) + 7 + 1);
	free(prompt_base);
	free(cwd);
	return (ret);
}
