/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/01 13:08:10 by nicknamemoh      ###   ########.fr       */
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

#endif
