#include "builtin.h"

int builtin_exit(char *args[], t_ld_map_env *env);

int builtin_exit(char *args[], t_ld_map_env *env)
{
	if (args[1] != NULL)
		exit(ft_atoi(args[1]));
	exit(EXIT_SUCCESS);
}
