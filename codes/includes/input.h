#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# include "types.h"

// ANSI terminal contrl characters
# define TERM_COLOR_RED "\033[0;31m"
# define TERM_COLOR_GREEN "\033[0;32m"
# define TERM_COLOR_YELLOW "\033[0;33m"
# define TERM_COLOR_BLUE "\033[0;34m"
# define TERM_COLOR_END "\033[0m"

// input_readline.c
char	*input_readline_f(void);

// input_sighandler.c
void	input_sighandler_setup(struct sigaction oldacts[2]);
void	input_sighandler_restore(struct sigaction oldacts[2]);
void	input_sighandler(int sig, siginfo_t *info, void *ucontext);
# define OLDACT_SIGINT 0
# define OLDACT_SIGQUIT 1

// input_terminal.c
void	input_terminal_setup(struct termios *oldterm);
void	input_terminal_restore(struct termios *oldterm);

// input_validator.c
t_bool	input_validate(const char *input);

#endif
