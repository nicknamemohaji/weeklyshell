/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:33 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/05 14:51:09 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_cd(char *args[], t_ld_map_env *env);

int	builtin_cd(char *args[], t_ld_map_env *env)
{
	char	*key_pwd;

	if (!builtin_check_argument_count((const char **)args, 2))
		return (EXIT_FAILURE);
	if (args[1] != NULL)
	{
		if (args[1][0] == '/')
		{
			if (access(args[1], F_OK | X_OK) != 0 || chdir(args[1]) != 0)
			{
				printf("no such file");
				return (EXIT_FAILURE);
			}
		}
		else if ((ft_strchr(args[1], '/') != NULL && ld_chdir(args[1]) != TRUE)
			|| (ft_strchr(args[1], '/') == NULL && chdir(args[1])))
			return (EXIT_FAILURE);
		key_pwd = ft_strdup("PWD");
		if (key_pwd == NULL)
			do_exit("builtin_cd.malloc");
		ldpre_env_add(key_pwd, getcwd(NULL, 0), env);
	}
	return (EXIT_SUCCESS);
}
