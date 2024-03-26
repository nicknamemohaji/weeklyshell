#include "builtin.h"
#include "utils.h"

int		 builtin_export(char *args[], t_ld_map_env *env);
static int  builtin_export_print(t_ld_map_env *env);

int builtin_export(char *args[], t_ld_map_env *env)
{
	int i;
	char *key;
	char *value;

	if (args[1] == NULL)
		return (builtin_export_print(env));
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			key = ft_strdup(args[i]);
			value = ft_strdup("");
		}
		else
		{
			key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			value = ft_strdup(ft_strchr(args[i], '=') + 1);
		}
		if (key == NULL || value == NULL)
			do_exit("builtin_export.malloc");
		ldpre_env_add(key, value, env);
		i++;
	}
	return (EXIT_SUCCESS);
}
