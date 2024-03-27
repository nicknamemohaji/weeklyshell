/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:41 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 06:47:19 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_exit(char *args[], t_ld_map_env *env);

int	builtin_exit(char *args[], t_ld_map_env *env)
{
	free_ld_map(env);
	if (args[1] != NULL)
		exit(ft_atoi(args[1]));
	exit(EXIT_SUCCESS);
}
