#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft.h"

typedef struct s_cmd
{
    char *cmd;
    int num_args;
    char **args;
} t_cmd;

int num_commands;
int file_fd;

void do_fork(int i, t_cmd *cmds, int *fd);
char *find_binary_path(char *cmd);


int main(int argc, char **argv)
{
    // parse the command line arguments
    // format: ./a.out cmd1 arg1 cmd2 arg1 cmd3 arg1
    num_commands = (argc - 1) / 2;
    t_cmd *cmds = malloc(sizeof(t_cmd) * num_commands);
    for (int i = 0; i < num_commands; i++)
    {
        cmds[i].cmd = find_binary_path(argv[i * 2 + 1]);
        if (cmds[i].cmd == NULL)
        {
            printf("command not found: %s\n", argv[i * 2 + 1]);
            exit(1);
        }
        cmds[i].num_args = 1;
        cmds[i].args = malloc(sizeof(char *) * 3);
        cmds[i].args[0] = cmds[i].cmd;
        cmds[i].args[1] = argv[i * 2 + 2];
        cmds[i].args[2] = NULL;
    }

    // create pipe
    int fds[2][2];
    if (pipe(fds[0]) != 0)
        exit(1);
    if (pipe(fds[1]) != 0)
        exit(1);
    
    // open file
    if ((file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
        exit(1);
    
    // create a child process for each command
    pid_t pid;
    int exit_status = -1;
    for (int i = 0; i < num_commands; i++)
    {
        // subshell
        if ((pid = fork()) == 0)
        {
            do_fork(i, cmds, (int[2]){fds[(i + 1) % 2][0], fds[i % 2][1]});
        }
        // loader
        else
        {
            printf("[%d]: (%d)\n", i, pid);
            printf("command [%s %s]\n", cmds[i].cmd, cmds[i].args[1]);
            wait(&exit_status);
            printf("loaded %s exited with status %d\n", cmds[i].cmd, exit_status);

            // close and reopen pipe to prevent deadlock
            close(fds[(i + 1) % 2][0]);
            close(fds[i % 2][1]);
            if (pipe(fds[(i + 1) % 2]) != 0)
                exit(1);
            }
    }

    // close fds
    // IDGAF about re-closing closed fds
    close(file_fd);
    close(fds[0][0]);
    close(fds[0][1]);
    close(fds[1][0]);
    close(fds[1][1]);
    
    printf("done!\n");
    return 0;
}

void do_fork(int i, t_cmd *cmds, int *fd)
{
    printf("executing %s\n", cmds[i].cmd);

    // duplicate pipe fd if neccessary
    if (i == num_commands - 1)
    {
        if (dup2(file_fd, 1) == -1)
            perror("dup2 - file to STDOUT");
    }
    else
    {
        if (dup2(fd[1], 1) == -1)
            perror("dup2 - PIPE to STDOUT");
    }
    if (i != 0)
    {
        if (dup2(fd[0], 0) == -1)
            perror("dup2 - PIPE to STDIN");
    }
    
    // close fds
    close(fd[0]);
    close(fd[1]);
    close(file_fd);

    // execute command
    execve(cmds[i].cmd, cmds[i].args, NULL);
}

char *find_binary_path(char *cmd)
{
    // check if absolute path
    if (access(cmd, F_OK | X_OK) == 0)
    {
        return (cmd);
    }

    // search in current directory
    char *tmp = getcwd(NULL, 0);
    char *tmp2 = ft_strjoin(tmp, "/");
    free(tmp);
    tmp = ft_strjoin(tmp2, cmd);
    free(tmp2);
    if (access(tmp, F_OK | X_OK) == 0)
        return tmp;

    // search env path
    char **paths = ft_split(getenv("PATH"), ':');
    char *path = NULL;
    for (int i = 0; paths[i] != NULL; i++)
    {
        tmp = ft_strjoin(paths[i], "/");
        tmp2 = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(tmp2, F_OK | X_OK) == 0)
        {
            path = tmp2;
            break;
        }
        free(tmp2);
    }
    free(paths);
    return path;
}