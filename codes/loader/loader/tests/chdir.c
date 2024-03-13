#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	printf("moving to %s\n", argv[1]);
	printf("prev: %s\n", getcwd(NULL, 0));
	printf("access: %d\n", access(argv[1], F_OK));
	errno = 0;
	printf("chdir: %d\n", chdir(argv[1]));
	printf("errno: %s\n", strerror(errno));
	printf("prev: %s\n", getcwd(NULL, 0));
}
