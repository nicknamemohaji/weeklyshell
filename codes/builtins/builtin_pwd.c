#include "builtin.h"
#include "utils.h"

int builtin_pwd(char *args[], t_ld_map_env *env);

int builtin_pwd(char *args[], t_ld_map_env *env)
{
	char	*pwd;

	pwd = ldpre_env_fetch("PWD", env);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
