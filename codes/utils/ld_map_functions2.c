/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ld_map_functions2.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nicknamemohaji <nicknamemohaji@student.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/19 00:50:17 by nicknamemoh	   #+#	#+#			 */
/*   Updated: 2024/03/27 05:31:42 by nicknamemoh	  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "types.h"
#include "utils.h"

t_ld_map_node	**ldpre_env_searchkey(char *key, t_ld_map_env *map);
char			*ldpre_env_fetch(char *key, t_ld_map_env *map);
void			ldpre_env_add(char *key, char *value,
					t_ld_map_env *map);
t_bool			ldpre_env_remove(char *key, t_ld_map_env *map);
static t_bool	validate_key_format(char *key);

/*
t_ld_map_node	**ldpre_env_searchkey(char *key, t_ld_map_env *map)
:param key: key to serach
:param map: pointer to map
:return: if key is not found, returns NULL pointer. if key is found, 
	returns node[2] = {*node, *prev}. use node[0] to access data, 
	node[1] to remove node from list

This should be internal function.
*/
t_ld_map_node	**ldpre_env_searchkey(char *key, t_ld_map_env *map)
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

	if (!validate_key_format(key))
	{
		printf("syntax error: [%s]\n", key);
		return (NULL);
	}
	node = ldpre_env_searchkey(key, map);
	if (node == NULL)
		return (NULL);
	else
		return ((node[0])->value);
}

void	ldpre_env_add(char *key, char *value, t_ld_map_env *map)
{
	t_ld_map_node	*node;
	char			*key_copy;
	char			*value_copy;

	if (!validate_key_format(key))
	{
		printf("syntax error: [%s]\n", key);
		return ;
	}
	ldpre_env_remove(key, map);
	node = malloc(sizeof(t_ld_map_node) * 1);
	if (node == NULL)
		do_exit("ldpre_env_add.malloc");
	key_copy = ft_strdup(key);
	value_copy = ft_strdup(value);
	if (key_copy == NULL || value_copy == NULL)
		do_exit("ldpre_env_add.ft_strdup");
	free(key);
	free(value);
	node->key = key_copy;
	node->value = value_copy;
	node->next = NULL;
	ld_map_node_attach(map, node);
	return ;
}

t_bool	ldpre_env_remove(char *key, t_ld_map_env *map)
{
	t_ld_map_node	**node;

	node = ldpre_env_searchkey(key, map);
	if (node == NULL)
		return (FALSE);
	if (node[1] == NULL)
		map->contents = node[0]->next;
	else
		node[1]->next = node[0]->next;
	free(node[0]->key);
	free(node[0]->value);
	free(node[0]);
	map->count--;
	return (TRUE);
}

/*
static t_bool	validate_key_format(char *key)
:param key: key string to validate
:return: TRUE if key matches requirements
*/
static t_bool	validate_key_format(char *key)
{
	if (!(ft_isalpha(*key) || *key == '_'))
		return (FALSE);
	while (ft_isalnum(*key) || *key == '_')
		key++;
	if (*key == '\0')
		return (TRUE);
	else
		return (FALSE);
}
