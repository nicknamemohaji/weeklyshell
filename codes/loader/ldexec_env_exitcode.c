/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_env_exitcode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:44:12 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 14:23:31 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char	*ldexec_env_exitcode_fetch_f(t_ld_map_env *env);
void	ldexec_env_exitcode_update(int code, t_ld_map_env *env);

/*
char	*ldexec_env_exitcode_fetch_f(t_ld_map_env *env)
:param env: environment variable map
:return: itoa'ed last exitcode

Fetches `$?` from map. `$?` is always at first node of env map. 

`$?` is not a valid key, so created special methods. user cannot access,
modify, delete to this environment variable, since fetch/add/remove interface
validates the key before doing action.
*/
char	*ldexec_env_exitcode_fetch_f(t_ld_map_env *env)
{
	char			*ret;
	t_ld_map_node	*node;

	node = env->contents;
	ret = ft_strdup(node->value);
	if (ret == NULL)
		do_exit("ldexec_env_exitcode_fetch_f.malloc");
	return (ret);
}

/*
void	ldexec_env_exitcode_update(int code, t_ld_map_env *env)
:param code: new status code
:param env: environment variable map

Update/Adds last status code(`$?`) to map
*/
void	ldexec_env_exitcode_update(int code, t_ld_map_env *env)
{
	t_ld_map_node	*node;
	t_ld_map_node	*next;

	node = env->contents;
	next = node->next;
	free(node->key);
	free(node->value);
	free(node);
	node = malloc(1 * sizeof(t_ld_map_node));
	if (node == NULL)
		do_exit("ldexec_env_exitcode_update.malloc");
	node->key = ft_strdup("?");
	if (node->key == NULL)
		do_exit("ldexec_env_exitcode_update.malloc");
	node->value = ft_itoa(code);
	if (node->value == NULL)
		do_exit("ldexec_env_exitcode_update.malloc");
	node->next = NULL;
	node->next = next;
	env->contents = node;
}
