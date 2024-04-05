/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:41 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 12:21:17 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int				builtin_exit(char *args[], t_ld_map_env *env);
static t_bool	check_digit(const char *c);
static t_bool	check_argumen_count(const char *args[]);

int	builtin_exit(char *args[], t_ld_map_env *env)
{
	printf("exit\n");
	if (!check_argumen_count((const char **) args))
		return (1);
	if (args[1] != NULL)
	{
		if (!check_digit(args[1]))
			exit (255);
		free_ld_map(env);
		exit(ft_atoi(args[1]));
	}
	else
		exit(EXIT_SUCCESS);
}

static t_bool	check_digit(const char *c)
{
	const char	*ptr;

	ptr = c;
	while (*c != '\0')
	{
		if (!ft_isdigit(*c))
		{
			printf("exit: %s: numeric argument required\n", ptr);
			return (FALSE);
		}
		c++;
	}
	return (TRUE);
}

static t_bool	check_argumen_count(const char *args[])
{
	int	count;

	count = 0;
	while (*args != NULL)
	{
		count++;
		args++;
	}
	if (count > 2)
	{
		printf("exit: too many arguments\n");
		return (FALSE);
	}
	else
		return (TRUE);
}