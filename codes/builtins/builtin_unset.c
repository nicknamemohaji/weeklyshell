/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:47 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 15:05:04 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_unset(char *args[], t_ld_map_env *env);

/*
int	builtin_unset(char *args[], t_ld_map_env *env)
:args: unsets keys given
:env: environment variables, used to unset
:return: execution result (always 0)
*/
int	builtin_unset(char *args[], t_ld_map_env *env)
{
	int	i;

	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i] != NULL)
		ldpre_env_remove(args[i++], env);
	return (EXIT_SUCCESS);
}
