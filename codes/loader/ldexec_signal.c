/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:04:37 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/17 15:07:38 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "input.h"
#include "types.h"
#include "utils.h"

void	ldexec_signal_setup(struct sigaction oldacts[2]);
void	ldexec_handler(int sig, siginfo_t *info, void *ucontext);

/*
void	ldexec_signal_setup(struct sigaction oldacts[2])
:param oldacts: sigaction array to store default handlers

Similar to input_sighandler_setup, but choose to ignore.
Shell environment after forking child should use this function.
Deactivates SIGINT(Ctrl + C) and SIGQUIT(Ctrl + \)

Stores previous signal handlers in *oldacts, making it available
to restore default behaviors.
*/
void	ldexec_signal_setup(struct sigaction oldacts[2])
{
	struct sigaction	action;
	sigset_t			mask;

	g_sigint = FALSE;
	if (sigemptyset(&mask) != 0)
		do_exit("ldexec_signal_setup.sigemptyset");
	action.sa_flags = 0 | SA_RESTART;
	action.sa_mask = mask;
	action.sa_sigaction = ldexec_handler;
	if (sigaction(SIGINT, &action, &oldacts[OLDACT_SIGINT]) != 0)
		do_exit("ldexec_signal_setup.sigaction");
	if (sigaction(SIGQUIT, &action, &oldacts[OLDACT_SIGQUIT]) != 0)
		do_exit("ldexec_signal_setup.sigaction");
}

void	ldexec_handler(int sig, siginfo_t *info, void *ucontext)
{
	write(1, "\n", 1);
	(void)sig;
	(void)info;
	(void)ucontext;
}
