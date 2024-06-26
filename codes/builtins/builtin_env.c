/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:39 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/15 15:02:39 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int			builtin_env(char *args[], t_ld_map_env *env);

/*
int	builtin_env(char *args[], t_ld_map_env *env)
:args: not used
:env: environment variables, used to print
:return: execution result (always 0)
*/
int	builtin_env(char *args[], t_ld_map_env *env)
{
	t_ld_map_node	*node;

	(void)args;
	node = (env->contents)->next;
	while (node != NULL)
	{
		if (*(node->value) != '\0')
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
