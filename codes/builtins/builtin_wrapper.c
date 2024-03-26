#include "builtin.h"
#include "utils.h"
#include "loader.h"

int		 builtin_wrapper(t_ld_struct_exec exec, t_ld_map_env *env);
static int  builtin_wrapper_run(char *args[], t_ld_map_env *env);
t_bool	  builtin_isbuiltin(char *name);

int builtin_wrapper(t_ld_struct_exec exec, t_ld_map_env *env)
{
	int exitcode;
	int stdout_fd;

	if (exec.redir.stdout != NULL || exec.pipe.stdin != -1)
	{
		stdout_fd = dup(STDOUT_FD);
		if (stdout_fd == -1)
			do_exit("builtin_wrapper.dup");
	}
	else
		stdout_fd = -1;
	ldexec_redir(exec.redir, exec.pipe, NULL);
	exitcode = builtin_wrapper_run(exec.argv, env);
	if (stdout_fd != -1)
	{
		if (close(STDOUT_FD) != 0 || dup2(stdout_fd, STDOUT_FD) == -1
			|| close(stdout_fd) != 0)
			do_exit("builtin_wrapper.close");
	}
	return (exitcode);
}

static int  builtin_wrapper_run(char *args[], t_ld_map_env *env)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		return (builtin_cd(args, env));
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (builtin_pwd(args, env));
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		return (builtin_echo(args, env));
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		return (builtin_exit(args, env));
	else if (ft_strncmp(args[0], "export", 6) == 0)
		return (builtin_export(args, env));
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		return (builtin_unset(args, env));
	return (EXIT_FAILURE);
}

t_bool  builtin_isbuiltin(char *name)
{
	if (ft_strncmp(name, "cd", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "pwd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "exit", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "export", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(name, "unset", 5) == 0)
		return (TRUE);
	return (FALSE);
}
