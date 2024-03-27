/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:35 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 06:43:25 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(char *args[], t_ld_map_env *env);

int	builtin_echo(char *args[], t_ld_map_env *env)
{
	int	i;

	(void) env;
	i = 1;
	if (args[1] != NULL
		&& ft_strlen(args[1]) == 2 && ft_strncmp(args[1], "-n", 2) == 0)
		i += 1;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (args[1] != NULL
		&& !(ft_strlen(args[1]) == 2 && ft_strncmp(args[1], "-n", 2) == 0))
		printf("\n");
	if (args[1] == NULL)
		printf("\n");
	return (EXIT_SUCCESS);
}
