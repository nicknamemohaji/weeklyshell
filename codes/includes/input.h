/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/28 02:02:11 by nicknamemoh      ###   ########.fr       */
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

// ANSI terminal contrl characters
# define TERM_COLOR_END "\001\033[m\002"
# define TERM_COLOR_RED "\001\033[31m\002"
# define TERM_COLOR_GREEN "\001\033[32m\002"
# define TERM_COLOR_YELLOW "\001\033[33m\002"
# define TERM_COLOR_BLUE "\001\033[34m\002"
// # define TERM_COLOR_END ""
// # define TERM_COLOR_RED ""
// # define TERM_COLOR_GREEN ""
// # define TERM_COLOR_YELLOW ""
// # define TERM_COLOR_BLUE ""

// input_readline.c

char	*input_readline_f(void);

// input_terminal.c

void	input_terminal_setup(struct termios *oldterm);
void	input_terminal_restore(struct termios *oldterm);

// input_validator.c

t_bool	input_validate(const char *input);

#endif
