/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:08 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/21 11:48:24 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	input_terminal_setup(struct termios *oldterm);
void	input_terminal_restore(struct termios *oldterm);

/*
void	input_terminal_setup(struct termios *oldterm)
:param oldterm: struct to store default terminal settings
*/
void	input_terminal_setup(struct termios *oldterm)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		do_exit("input_terminal_setup.tcgetattr");
	*oldterm = term;
	term.c_lflag |= (ECHO | ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		do_exit("input_terminal_setup.tcsetattr");
}

/*
void	input_terminal_restore(struct termios *oldterm)
:param oldterm: struct to store default terminal settings
*/
void	input_terminal_restore(struct termios *oldterm)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, oldterm) != 0)
		do_exit("input_terminal_restore.tcsetattr");
}
