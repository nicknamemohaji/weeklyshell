/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_map_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:50:17 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/19 01:48:24 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"

static t_ld_map_node	**find_key_from_map(char *key, t_ld_map_env *map);
char					*ldpre_env_fetch(char *key, t_ld_map_env *map);
void					ldpre_env_add(char *key, char *value,
							t_ld_map_env *map);
t_bool					ldpre_env_remove(char *key, t_ld_map_env *map);

static t_ld_map_node	**find_key_from_map(char *key, t_ld_map_env *map)
{
	t_ld_map_node	*node;
	t_ld_map_node	*prev;
	const size_t	key_len = ft_strlen(key);

	node = map->contents;
	prev = NULL;
	while (node != NULL)
	{
		if (ft_strlen(node->key) == key_len
			&& ft_strncmp(node->key, key, key_len) == 0)
			break ;
		prev = node;
		node = node->next;
	}
	if (node == NULL)
		return (NULL);
	else
		return ((t_ld_map_node *[2]){node, prev});
}

char	*ldpre_env_fetch(char *key, t_ld_map_env *map)
{
	t_ld_map_node	**node;

	node = find_key_from_map(key, map);
	if (node == NULL)
		return (NULL);
	else
		return ((node[0])->value);
}

void	ldpre_env_add(char *key, char *value, t_ld_map_env *map)
{
	t_ld_map_node	*node;

	ldpre_env_remove(key, map);
	node = malloc(sizeof(t_ld_map_node) * 1);
	if (node == NULL)
		do_exit("ldpre_env_add.malloc");
	node->key = key;
	node->value = value;
	ld_map_node_attach(map, node);
	return ;
}

t_bool	ldpre_env_remove(char *key, t_ld_map_env *map)
{
	t_ld_map_node	**node;

	node = find_key_from_map(key, map);
	if (node == NULL)
		return (FALSE);
	if (node[1] == NULL)
		map->contents = node[0]->next;
	else
		node[1]->next = node[0]->next;
	free(node[0]->key);
	free(node[0]->value);
	free(node[0]);
	return (TRUE);
}
