/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:47 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 06:04:48 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_unset(char *args[], t_ld_map_env *env);

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
