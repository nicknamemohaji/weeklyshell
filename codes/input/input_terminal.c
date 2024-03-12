#include "input.h"

void	input_terminal_setup(struct termios *oldterm);
void	input_terminal_restore(struct termios *oldterm);

/*
void	input_terminal_setup(struct termios *oldterm)
:param oldterm: struct to store default terminal settings
*/
void	input_terminal_setup(struct termios *oldterm)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	*oldterm = term;
	term.c_lflag |= (ECHO | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/*
void	input_terminal_restore(struct termios *oldterm)
:param oldterm: struct to store default terminal settings
*/
void	input_terminal_restore(struct termios *oldterm)
{
	tcsetattr(STDIN_FILENO, TCSANOW, oldterm);
}
