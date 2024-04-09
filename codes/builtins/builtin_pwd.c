/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:45 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 13:47:00 by kyungjle         ###   ########.fr       */
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
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		ldpre_env_add(ft_strdup("PWD"), pwd, env);
	}
	else
		printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
