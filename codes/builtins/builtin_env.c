/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:39 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/04 17:47:08 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	builtin_env(char *args[], t_ld_map_env *env);
int	builtin_env_print(t_ld_map_env *env);

int	builtin_env(char *args[], t_ld_map_env *env)
{
	(void)args;
	return (builtin_env_print(env));
}

int	builtin_env_print(t_ld_map_env *env)
{
	t_ld_map_node	*node;

	node = env->contents;
	while (node != NULL)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
