/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sighandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:05 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/10 14:23:49 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	ldexec_sigign_setup(struct sigaction oldacts[2]);
void	input_sighandler_setup(struct sigaction oldacts[2]);
void	input_sighandler_restore(struct sigaction oldacts[2]);
void	input_sighandler(int sig, siginfo_t *info, void *ucontext);
int		rl_event_void(void);

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
	if (sigemptyset(&mask) != 0
		|| sigaddset(&mask, SIGINT) != 0 || sigaddset(&mask, SIGQUIT) != 0)
		do_exit("input_sighandler_setup.sigemptyset");
	rl_catch_signals = 0;
	rl_event_hook = rl_event_void;
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
}

/*
void	input_sighandler(int sig, siginfo_t *info, void *ucontext)
:param sig: defined in sigaction(2). not used 
:param info: defined in sigaction(2). not used
:param ucontext: defined in sigaction(2). not used

signal handler for SIGINT in interactive mode.
Modifies g_sigint variable to notice that sigint has occured.

Modified g_sigint value will be checked in rl_event_void function,
which is registered as rl_event_hook, to finish current input.
*/
void	input_sighandler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	g_sigint = TRUE;
}

int	rl_event_void(void)
{
	if (g_sigint == TRUE)
	{
		rl_done = 1;
		rl_replace_line("", 0);
	}
	if (errno != 0)
		perror("readline");
	return (0);
}