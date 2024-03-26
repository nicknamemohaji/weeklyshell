#include "builtin.h"

int builtin_echo(char *args[], t_ld_map_env *env);

int builtin_echo(char *args[], t_ld_map_env *env)
{
	int i;

	i = 1;
	if (args[1] != NULL
		&& ft_strlen(args[1]) == 3 && ft_strncmp(args[1], "-n", 2) == 0)
		i += 1;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (args[1] != NULL
		&& ft_strlen(args[1]) == 3 && ft_strncmp(args[1], "-n", 2) != 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
