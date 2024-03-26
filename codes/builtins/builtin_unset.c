#include "builtin.h"
#include "utils.h"

int builtin_unset(char *args[], t_ld_map_env *env);

int builtin_unset(char *args[], t_ld_map_env *env)
{
	int i;

	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i] != NULL)
		ldpre_env_remove(args[i++], env);
	return (EXIT_SUCCESS);
}
