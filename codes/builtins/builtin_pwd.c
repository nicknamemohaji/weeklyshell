/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:45 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 06:07:28 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_pwd(char *args[], t_ld_map_env *env);

int	builtin_pwd(char *args[], t_ld_map_env *env)
{
	char	*pwd;

	(void) args;
	pwd = ldpre_env_fetch("PWD", env);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
