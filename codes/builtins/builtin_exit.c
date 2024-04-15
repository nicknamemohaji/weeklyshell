/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:41 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/15 15:13:18 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int				builtin_exit(char *args[], t_ld_map_env *env);
static t_bool	check_digit(const char *c);
t_bool			builtin_check_argument_count(const char *args[],
					int limit, char *cmd);

/*
int	builtin_exit(char *args[], t_ld_map_env *env)
:args: arguments
:env: environment variables, used to free when exiting
:return: 1 if execution fails. if execution was successful, the process
will return with argument given (0 if no argument given)
*/
int	builtin_exit(char *args[], t_ld_map_env *env)
{
	if (!builtin_check_argument_count((const char **) args, 2, "exit"))
		return (1);
	if (args[1] != NULL)
	{
		if (!check_digit(args[1]))
			exit (255);
		free_ld_map(env);
		write(2, "exit\n", 5);
		exit(ft_atoi(args[1]));
	}
	write(2, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

/*
static t_bool	check_digit(const char *c)
:c: string to be checked
:return: true if all characters in string is digit

check for string is only digit
*/
static t_bool	check_digit(const char *c)
{
	const char	*ptr;
	char		*msg;

	ptr = c;
	while (*c != '\0')
	{
		if (!ft_isdigit(*c))
		{
			msg = malloc((ft_strlen(ptr) + 36) * sizeof(char));
			*msg = '\0';
			ft_sprintf(msg, "exit: %s: numeric argument required\n", ptr);
			write(2, msg, ft_strlen(msg));
			free(msg);
			return (FALSE);
		}
		c++;
	}
	return (TRUE);
}

/*
t_bool	builtin_check_argument_count(const char *args[], int limit, char *cmd)
:args: argument list to be checked
:limit: limit
:cmd: command name for printing trace
:return: true if arguments are given less than limit

checks for how many arguments given, checking for max argument count
*/
t_bool	builtin_check_argument_count(const char *args[], int limit, char *cmd)
{
	int	count;

	count = 0;
	while (*args != NULL)
	{
		count++;
		args++;
	}
	if (count > limit)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": too many arguments\n", 21);
		return (FALSE);
	}
	else
		return (TRUE);
}
