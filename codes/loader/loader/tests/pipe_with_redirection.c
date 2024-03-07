#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    /*
    Test fails. HOW TO REDIRECT AND PIPE AT THE SAME TIME??
    */
	int fd[2];
	pid_t pid;

	if (pipe(fd) != 0)
		exit(1);
	int fd_dup = dup(fd[0]);

	printf("before fork\n");
	if ((pid = fork()) == 0)
	{
		if ((pid = fork()) == 0)	// grandchild
		{
			printf("[G] grandchild pid %d\n", getpid());
			printf("[G] reading pipe\n");

			dup2(fd[0], 0);

			char buf[100] = {'\0'};
			if (read(0, buf, 100) < 0)
				perror("[G] read error");
			else
				printf("[G] pipe content:[[%s]]\n", buf);
		}
		else	// child 
		{
			printf("[C] child pid %d\n", getpid());
			printf("[C] writing pipe\n");

			int fd_stdout = dup(1);
			dup2(fd[1], 1);

			printf("WRITING TO PIPE!!!!!\n");
			dprintf(fd_stdout, "[C] Write done\n");
			wait(NULL);
		}
	}
	else	// parent
	{
		printf("[P] parent pid %d\n", getpid());
		printf("[P] child %d exited\n", wait(NULL));

		printf("[P] reading pipe contents...\n");
		char buf[100] = {'\0'};
		if (read(fd_dup, buf, 100) < 0)
			perror("[P] read error");
		else
			printf("[P] content: [[%s]]\n", buf);


		close(fd[0]);
		close(fd[1]);
		close(fd_dup);
	}

	printf("exiting %d\n", getpid()); 
}
