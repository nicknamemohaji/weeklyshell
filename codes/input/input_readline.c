/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:01 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 16:39:52 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

static char	*make_prompt_f(t_ld_map_env *env);
char		*input_readline_f(t_ld_map_env *env);

/*
char	*input_readline_f(t_ld_map_env *env)
:env: environemnt variable map, for getting $PWD
:return: string containg user's input.

Weeklyshell's input module wrapper function. Prompts interactive shell
and returns user's input. Uses GNU readline library functions to perform
actions, and uses history library to save inputs.

Caller should free the returned pointer after use.
*/
char	*input_readline_f(t_ld_map_env *env)
{
	char				*input;
	char				*prompt;
	struct sigaction	oldacts[2];
	struct termios		oldterm;

	prompt = make_prompt_f(env);
	input_sighandler_setup(oldacts);
	input_terminal_setup(&oldterm);
	g_sigint = FALSE;
	input = readline(prompt);
	input_sighandler_restore(oldacts);
	input_terminal_restore(&oldterm);
	if (input != NULL && *input != '\0')
		add_history(input);
	else if (input != NULL && *input == '\0')
		ldexec_env_exitcode_update(1, env);
	free(prompt);
	return (input);
}

/*
static char	*make_prompt_f(t_ld_map_env *env)
:env: environemnt variable map, for getting $PWD
:return: string containg prompt string.

Makes shell prompt containing Current Working Directory (CWD). 
cwd info is fetched from $PWD value in environment variables.
Caller should free the returned pointer after use.
*/
static char	*make_prompt_f(t_ld_map_env *env)
{
	char	*ret;
	char	*prompt_base;
	char	*cwd;

	prompt_base = ft_strdup(TERM_COLOR_GREEN "weeklyshell"
			TERM_COLOR_END ":" TERM_COLOR_YELLOW);
	if (prompt_base == NULL)
		do_exit("make_prompt_f.malloc");
	cwd = ldpre_env_fetch("PWD", env);
	if (cwd == NULL)
		cwd = do_getcwd_f(NULL, 0);
	ret = malloc(ft_strlen(prompt_base) + ft_strlen(cwd) + 7 + 1);
	if (ret == NULL)
		do_exit("make_prompt_f.malloc");
	ft_strlcpy(ret, prompt_base, ft_strlen(prompt_base) + 1);
	ft_strlcat(ret, cwd, ft_strlen(ret) + ft_strlen(cwd) + 1);
	ft_strlcat(ret, TERM_COLOR_END "$ ", ft_strlen(ret) + 7 + 1);
	free(prompt_base);
	return (ret);
}
