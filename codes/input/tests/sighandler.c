#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int sig, siginfo_t *info, void *ucontext);
void sighandler_setup(void);

int main(void)
{
    printf("pid: %d\n", getpid());

    // set signal handlers
    sighandler_setup();
    
    // wait for signals
    for (int i=0; i<5; i++)
    {
        printf("waiting for signal\n");
        pause();
    }
	return 0;
}

void sighandler_setup(void)
{
    struct sigaction action;
	sigset_t mask;

    // signal mask
	if (sigemptyset(&mask) != 0)
		exit(1);
    
    // set sigaction
	action.sa_sigaction = sighandler;
	action.sa_flags = 0 | SA_SIGINFO;
	action.sa_mask = mask;

    // register signals
	if (
        sigaction(SIGINT, &action, NULL) != 0       // ctrl + c
		|| sigaction(SIGTSTP, &action, NULL) != 0   // ctrl + z
		|| sigaction(SIGQUIT, &action, NULL) != 0   // ctrl + '\'
    )
		exit(1);
}

void sighandler(int sig, siginfo_t *info, void *ucontext)
{
    (void) ucontext;
    (void) info;

    printf("received signal: %s\n", strsignal(sig));
}
