/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:54 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/05 12:46:00 by kyungjle         ###   ########.fr       */
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
