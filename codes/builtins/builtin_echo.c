/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:54 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 15:01:47 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int				builtin_echo(char *args[], t_ld_map_env *env);
static t_bool	parse_args(char *args[], int *index);

/*
int	builtin_echo(char *args[], t_ld_map_env *env)
:args: arguments
:env: not used
:return: execution result(always 0)
*/
int	builtin_echo(char *args[], t_ld_map_env *env)
{
	int		index;
	t_bool	print_nl;

	(void) env;
	index = 1;
	print_nl = parse_args(args, &index);
	while (args[index] != NULL)
	{
		printf("%s", args[index]);
		if (args[index + 1] != NULL)
			printf(" ");
		index++;
	}
	if (print_nl || args[1] == NULL)
		printf("\n");
	return (EXIT_SUCCESS);
}

/*
static t_bool	parse_args(char *args[], int *index)
:args: arguments to be checked
:index: pointer of index variable to be changed
:return: TRUE if `-n` argument was given

checks for `-n` in arguments, and moves the index if it is an argument
*/
static t_bool	parse_args(char *args[], int *index)
{
	t_bool	ret;
	int		i;

	ret = TRUE;
	while (args[*index] != NULL)
	{
		if (args[*index][0] != '-')
			break ;
		i = 1;
		while (args[*index][i] != '\0')
		{
			if (args[*index][i] != 'n')
				return (ret);
			i += 1;
		}
		ret = FALSE;
		*index += 1;
	}
	return (ret);
}
