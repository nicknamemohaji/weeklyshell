/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sighandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:05 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/17 15:03:04 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

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

Signal handler use rl_done variable of readline library, which needs
event hook function to be checked. Disabled readline library's own signal
handler to add consistency.
*/
void	input_sighandler_setup(struct sigaction oldacts[2])
{
	struct sigaction	action;
	sigset_t			mask;

	g_sigint = FALSE;
	if (sigemptyset(&mask) != 0
		|| sigaddset(&mask, SIGINT) != 0 || sigaddset(&mask, SIGQUIT) != 0)
		do_exit("input_sighandler_setup.sigemptyset");
	rl_event_hook = rl_event_void;
	rl_catch_signals = 0;
	action.sa_flags = 0 | SA_SIGINFO;
	action.sa_flags &= ~SA_RESTART;
	action.sa_mask = mask;
	action.sa_sigaction = input_sighandler;
	if (sigaction(SIGINT, &action, &oldacts[OLDACT_SIGINT]) != 0)
		do_exit("input_sighandler_setup.sigaction");
	if (sigaction(SIGQUIT, &action, &oldacts[OLDACT_SIGQUIT]) != 0)
		do_exit("input_sighandler_setup.sigaction");
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
:param sig: signal number
:param info: defined in sigaction(2). not used
:param ucontext: defined in sigaction(2). not used

signal handler for SIGINT in interactive mode.
Modifies g_sigint variable to notice that sigint has occured.
(on SIGINT only; on SIGQUIT, the signal is ignored)

changing non-atomic variables and calling non-safe
functions violates safety. to ensure signal safety, signal handler will
only change sig_atomic_t variable (g_sigint). 
Modified g_sigint value will be checked in rl_event_void function,
which is registered as rl_event_hook, to finish current input.
*/
void	input_sighandler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	(void) sig;
	if (sig == SIGINT)
		g_sigint = TRUE;
}

/*
int	rl_event_void(void)

event hook function for readline, registered via rl_event_hook variable.
registering rl_event_hook function makes rl_done variable effective.

this hook will empty input buffer and finish readline function when g_sigint
is set to TRUE. otherwise, it does nothing. 
*/
int	rl_event_void(void)
{
	if (g_sigint == TRUE)
	{
		rl_done = 1;
		rl_replace_line("", 0);
	}
	return (0);
}
