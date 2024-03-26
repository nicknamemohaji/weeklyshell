#include "builtin.h"
#include "utils.h"

int	builtin_cd(char *args[], t_ld_map_env *env);

int	builtin_cd(char *args[], t_ld_map_env *env)
{
	char	*key_PWD;

	if (args[1] != NULL)
	{
		if (ld_chdir(args[1]) != TRUE)
			return (EXIT_FAILURE);
		key_PWD = ft_strdup("PWD");
		ldpre_env_add(key_PWD, getcwd(NULL, 0), env);
	}
	return (EXIT_SUCCESS);
}
