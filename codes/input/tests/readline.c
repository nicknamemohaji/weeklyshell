#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <termios.h>

# define TERM_COLOR_RED "\033[0;31m"
# define TERM_COLOR_GREEN "\033[0;32m"
# define TERM_COLOR_YELLOW "\033[0;33m"
# define TERM_COLOR_BLUE "\033[0;34m"
# define TERM_COLOR_END "\033[0m"

void sighandler(int sig, siginfo_t *info, void *ucontext);
void sig_and_term_setup(struct sigaction *oldacts, struct termios *oldterm);
void sig_and_term_restore(struct sigaction *oldacts, struct termios *oldterm);
char *make_prompt(void);

int main(void)
{
    char                *input;
    char                *prompt;
    struct sigaction    oldacts[2];
    struct termios      oldterm;

    while (1)
    {
        prompt = make_prompt();
        sig_and_term_setup(oldacts, &oldterm);
        input = readline(prompt);
        sig_and_term_restore(oldacts, &oldterm);

        if (input == NULL)
            break;
        if (*input != '\0')
            add_history(input);
        printf("You entered: %s\n", input);

        free(input);
        free(prompt);
    }

    free(prompt);
    free(input);
    rl_clear_history();
}

void sig_and_term_restore(struct sigaction *oldacts, struct termios *oldterm)
{
    sigaction(SIGINT, &oldacts[0], NULL);
    sigaction(SIGQUIT, &oldacts[1], NULL);
    tcsetattr(STDIN_FILENO, TCSANOW, oldterm);
}

void sig_and_term_setup(struct sigaction *oldacts, struct termios *oldterm)
{
    struct sigaction    action;
    struct termios      term;
	sigset_t            mask;

    // signal mask
	if (sigemptyset(&mask) != 0)
		exit(1);
    sigaddset(&mask, SIGINT);
    
    // sigaction
	action.sa_flags = 0 | SA_SIGINFO;
	action.sa_mask = mask;

    // register signals
	action.sa_sigaction = sighandler;                    // on SIGINT, call sighandler
	if (sigaction(SIGINT, &action, &oldacts[0]) != 0)    // ctrl + c
		exit(1);
    action.sa_handler = SIG_IGN;                         // on SIGQUIT, ignore
    if (sigaction(SIGQUIT, &action, &oldacts[1]) != 0)   // ctrl + '\'
        exit(1);
    
    // terminal
    tcgetattr(STDIN_FILENO, &term);
    *oldterm = term;
    term.c_lflag |= (ECHO | ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/*
ARGHHHHHHH! WTF IS SIGNAL SAFETY!!!!! IDC!!!!!!!!
*/
void sighandler(int sig, siginfo_t *info, void *ucontext)
{
    (void) ucontext;
    (void) info;
    (void) sig;

    write(1, "\n", 1);
    rl_on_new_line();               // unsafe function (changes global state)
    rl_replace_line("", 0);         // unsafe function (changes global state)
    rl_redisplay();                 // unsafe function (changes global state)
}

char *make_prompt(void)
{
    char    *ret;
    char    *temp;
    char    *temp2;

    temp = strdup(TERM_COLOR_GREEN "weeklyshell" TERM_COLOR_END ":" TERM_COLOR_YELLOW);
    temp2 = getcwd(NULL, 0);
    ret = malloc(strlen(temp) + strlen(temp2) + 6 + 1);
    strncpy(ret, temp, strlen(temp) + 1);
    strncat(ret, temp2, strlen(ret) + strlen(temp2) + 1);
    strncat(ret, TERM_COLOR_END "$ ", strlen(ret) + 6 + 1);
    free(temp);
    free(temp2);
    return (ret);
}