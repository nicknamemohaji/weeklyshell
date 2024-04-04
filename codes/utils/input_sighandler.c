/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sighandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:05 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/21 17:30:13 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ldexec_sigign_setup(struct sigaction oldacts[2]);
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

	g_sigint = FALSE;
	if (sigemptyset(&mask) != 0 || sigaddset(&mask, SIGINT) != 0)
		do_exit("input_sighandler_setup.sigemptyset");
	action.sa_flags = 0 | SA_SIGINFO;
	action.sa_flags &= ~SA_RESTART;
	action.sa_mask = mask;
	action.sa_sigaction = input_sighandler;
	if (sigaction(SIGINT, &action, &oldacts[OLDACT_SIGINT]) != 0)
		do_exit("input_sighandler_setup.sigaction");
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, &oldacts[OLDACT_SIGQUIT]) != 0)
		do_exit("input_sighandler_setup.sigaction");
}

/*
void	ldexec_sigign_setup(struct sigaction oldacts[2])
:param oldacts: sigaction array to store default handlers

Similar to input_sighandler_setup, but choose to ignore. 
Shell environment after forking child should use this function.
Deactivates SIGINT(Ctrl + C) and SIGQUIT(Ctrl + \)

Stores previous signal handlers in *oldacts, making it available
to restore default behaviors.
*/
void	ldexec_sigign_setup(struct sigaction oldacts[2])
{
	struct sigaction	action;
	sigset_t			mask;

	g_sigint = FALSE;
	if (sigemptyset(&mask) != 0)
		do_exit("ldexec_sigign_setup.sigemptyset");
	action.sa_flags = 0 | SA_RESTART;
	action.sa_mask = mask;
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &action, &oldacts[OLDACT_SIGINT]) != 0)
		do_exit("ldexec_sigign_setup.sigaction");
	if (sigaction(SIGQUIT, &action, &oldacts[OLDACT_SIGQUIT]) != 0)
		do_exit("ldexec_sigign_setup.sigaction");
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
Modifies g_sigint variable to notice that sigint has occured,
and changes readline state to print next prompt.

Note) it uses signal unsafe functions(readline library),
but using signal mask prevents handler to be reentranced.
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
