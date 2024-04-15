/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:45 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/15 15:11:11 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_pwd(char *args[], t_ld_map_env *env);

/*
int	builtin_pwd(char *args[], t_ld_map_env *env)
:args: not used
:env: environment variables, used to get PWD
:return: execution result (always 0)
*/
int	builtin_pwd(char *args[], t_ld_map_env *env)
{
	char	*pwd;

	(void) args;
	pwd = ldpre_env_fetch("PWD", env);
	if (pwd == NULL)
	{
		pwd = do_getcwd_f(NULL, 0);
		ldpre_env_add(ft_strdup("PWD"), pwd, env);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
