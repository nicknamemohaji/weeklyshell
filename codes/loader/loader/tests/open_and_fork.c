#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd = open("TESTFILE", O_WRONLY | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    printf("file %s fd %d\n", "TESTFILE", fd);
    
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0) // child
    {
        dprintf(fd, "child\n");
    }
    else // parent 
    {
        usleep(1000);
        dprintf(fd, "parent\n");
    }
    close(fd);
    return 0;
}