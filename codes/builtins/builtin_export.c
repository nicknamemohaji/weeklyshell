/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:43 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/04 17:47:28 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_export(char *args[], t_ld_map_env *env);

int	builtin_export(char *args[], t_ld_map_env *env)
{
	int		i;
	char	*key;
	char	*value;

	// TODO 정렬된 상태로 출력
	if (args[1] == NULL)
		return (builtin_env_print(env));
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			key = ft_strdup(args[i]);
			value = ft_strdup("");
		}
		else
		{
			key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			value = ft_strdup(ft_strchr(args[i], '=') + 1);
		}
		if (key == NULL || value == NULL)
			do_exit("builtin_export.malloc");
		ldpre_env_add(key, value, env);
		i++;
	}
	return (EXIT_SUCCESS);
}
