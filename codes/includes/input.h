/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/05 16:19:20 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

# include "types.h"

// input_readline.c

char	*input_readline_f(void);

// input_terminal.c

void	input_terminal_setup(struct termios *oldterm);
void	input_terminal_restore(struct termios *oldterm);

// input_validator.c

t_bool	input_validate(const char *input);

// input_sighandler.c
# define OLDACT_SIGINT 0
# define OLDACT_SIGQUIT 1

void	input_sighandler_setup(struct sigaction oldacts[2]);
void	input_sighandler_restore(struct sigaction oldacts[2]);
void	input_sighandler(int sig, siginfo_t *info, void *ucontext);
void	ldexec_sigign_setup(struct sigaction oldacts[2]);

#endif
