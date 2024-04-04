/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:33 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/01 15:30:21 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_cd(char *args[], t_ld_map_env *env);

int	builtin_cd(char *args[], t_ld_map_env *env)
{
	char	*key_pwd;

	if (args[1] != NULL)
	{
		if (args[1][0] == '/')
		{
			if (access(args[1], F_OK | X_OK) != 0 || chdir(args[1]) != 0)
				return (EXIT_FAILURE);
		}
		else if (ld_chdir(args[1]) != TRUE)
			return (EXIT_FAILURE);
		key_pwd = ft_strdup("PWD");
		if (key_pwd == NULL)
			do_exit("builtin_cd.malloc");
		ldpre_env_add(key_pwd, getcwd(NULL, 0), env);
	}
	return (EXIT_SUCCESS);
}
