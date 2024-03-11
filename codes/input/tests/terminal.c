#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <readline/readline.h>

struct termios new_term;
# define STDIN_FD 0

int main(void)
{
    signal(SIGINT, SIG_IGN);

    tcgetattr(STDIN_FD, &new_term);
    printf("ECHO: %d\n", new_term.c_lflag & ECHO);
    printf("ECHOCTL: %d\n", new_term.c_lflag & ECHOCTL);
    new_term.c_lflag |= (ECHO | ECHOCTL);
    tcsetattr(STDIN_FD, TCSANOW, &new_term);
    while (1)
        readline("prompt: ");
}