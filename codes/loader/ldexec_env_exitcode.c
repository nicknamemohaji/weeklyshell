/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_env_exitcode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:44:12 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 17:39:55 by kyungjle         ###   ########.fr       */
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

Fetches `$?` from map. `$?` is registered when previous execution finished,
so it might not exist. bash's default is 0, so we follow bash's behavior.

`$?` is not a valid key, so created special methods. user cannot access,
modify, delete to this environment variable, since fetch/add/remove interface
validates the key before doing action.
*/
char	*ldexec_env_exitcode_fetch_f(t_ld_map_env *env)
{
	char			*ret;
	t_ld_map_node	**nodes;

	nodes = ldpre_env_searchkey("?", env);
	if (nodes == NULL)
		ret = ft_itoa(0);
	else
		ret = ft_strdup(nodes[0]->value);
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
	t_ld_map_node	**nodes;
	t_ld_map_node	*node;

	nodes = ldpre_env_searchkey("?", env);
	if (nodes != NULL)
	{
		nodes[1]->next = nodes[0]->next;
		free(nodes[0]->key);
		free(nodes[0]->value);
		free(nodes[0]);
	}
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
	ld_map_node_attach(env, node);
}
