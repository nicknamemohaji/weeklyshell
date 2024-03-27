/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:33 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 06:05:30 by nicknamemoh      ###   ########.fr       */
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
		if (ld_chdir(args[1]) != TRUE)
			return (EXIT_FAILURE);
		key_pwd = ft_strdup("PWD");
		ldpre_env_add(key_pwd, getcwd(NULL, 0), env);
	}
	return (EXIT_SUCCESS);
}
