/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sighandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:05 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/14 02:43:00 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	input_sighandler_setup(struct sigaction oldacts[2]);
void	input_sighandler_restore(struct sigaction oldacts[2]);
void	input_sighandler(int sig, siginfo_t *info, void *ucontext);

/*
void	input_sighandler_setup(struct sigaction oldacts[2])
:param oldacts: sigaction array to store default handlers

Registers handler for SIGINT(Ctrl + C) and SIGQUIT(Ctrl + \),
making bash-like interactive shell behavior.
Stores previous signal handlers in *oldacts, making it available
to restore default behaviors.
*/
void	input_sighandler_setup(struct sigaction oldacts[2])
{
	struct sigaction	action;
	sigset_t			mask;

	if (sigemptyset(&mask) != 0 || sigaddset(&mask, SIGINT))
	{
		perror("error while prerparing sighandler");
		exit(EXIT_FAILURE);
	}
	action.sa_flags = 0 | SA_SIGINFO;
	action.sa_mask = mask;
	action.sa_sigaction = input_sighandler;
	if (sigaction(SIGINT, &action, &oldacts[OLDACT_SIGINT]) != 0)
	{
		perror("error while registering sighandler");
		exit(EXIT_FAILURE);
	}
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, &oldacts[OLDACT_SIGQUIT]) != 0)
	{
		perror("error while registering sighandler");
		exit(EXIT_FAILURE);
	}
	g_sigint = FALSE;
}

/*
void	input_sighandler_restore(struct sigaction oldacts[2])
:param oldacts: sigaction array to store default handlers

Restores default signal handler, making child process it loads
handles SIGINT and SIGQUIT as they were.
*/
void	input_sighandler_restore(struct sigaction oldacts[2])
{
	sigaction(SIGINT, &oldacts[OLDACT_SIGINT], NULL);
	sigaction(SIGQUIT, &oldacts[OLDACT_SIGQUIT], NULL);
	g_sigint = FALSE;
}

/*
void	input_sighandler(int sig, siginfo_t *info, void *ucontext)
:param sig: defined in sigaction(2)
:param info: defined in sigaction(2)
:param ucontext: defined in sigaction(2)

signal handler for SIGINT in interactive mode. 
note that it uses signal unsafe functions(readline library). 
but using signal mask prevents handler to be executed again,
so i guess it'll be fine.
*/
void	input_sighandler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	g_sigint = TRUE;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
