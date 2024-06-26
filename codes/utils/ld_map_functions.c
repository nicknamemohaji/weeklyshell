/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_map_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:09:12 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 15:15:08 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"

t_ld_map_env	*ldpre_env_fromenvp_f(char **envp);
void			ld_map_node_attach(t_ld_map_env *map, t_ld_map_node *node);
char			**ldpre_env_toenvp_f(t_ld_map_env *map);
void			free_ld_map(t_ld_map_env *map);

/*
t_ld_map_env	*ldpre_env_fromenvp_f(char **envp)
:param envp: string array containing environment varaibles
	(likely on main function's argument)
:return: created map structure

Caller should free the returned pointer after use.
(use free_ld_map function)
*/
t_ld_map_env	*ldpre_env_fromenvp_f(char **envp)
{
	t_ld_map_env	*ret;
	t_ld_map_node	*node;
	int				count;

	ret = malloc(1 * sizeof(t_ld_map_env));
	if (ret == NULL)
		do_exit("ldpre_env_fromenvp_f.malloc");
	count = 0;
	ret->contents = NULL;
	while (*envp != NULL)
	{
		node = malloc(1 * sizeof(t_ld_map_node));
		if (ret == NULL)
			do_exit("ldpre_env_fromenvp_f.malloc");
		node->next = NULL;
		ld_map_node_attach(ret, node);
		node->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		node->value = ft_substr(*envp,
				ft_strlen(node->key) + 1, ft_strlen(*envp));
		envp++;
		count++;
	}
	ret->count = count;
	return (ret);
}

/*
void	ld_map_node_attach(t_ld_map_env *map, t_ld_map_node *node)
:param map: pointer to map
:param node: node to append

Add new node to map
*/
void	ld_map_node_attach(t_ld_map_env *map, t_ld_map_node *node)
{
	t_ld_map_node	*prev;

	if (map->contents == NULL)
		map->contents = node;
	else
	{
		prev = map->contents;
		while (prev->next != NULL)
		{
			prev = prev->next;
		}
		prev->next = node;
	}
}

/*
void	free_ld_map(t_ld_map_env *map)
:param map: map to free
*/
void	free_ld_map(t_ld_map_env *map)
{
	t_ld_map_node	*node;

	node = map->contents;
	while (node != NULL)
	{
		map->contents = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = map->contents;
	}
	free(map);
}

/*
char	**ldpre_env_toenvp_f(t_ld_map_env *map)
:param map: pointer to map
:return: string array containing environment varaibles, envp style

Caller should free the returned pointer after use.
(use free_ft_split function)
*/
char	**ldpre_env_toenvp_f(t_ld_map_env *map)
{
	int				index;
	char			**ret;
	t_ld_map_node	*node;

	ret = malloc(sizeof(char *) * (map->count + 1));
	if (ret == NULL)
		do_exit("ldpre_env_toenvp_f.malloc");
	index = 0;
	node = (map->contents)->next;
	while (++index <= map->count)
	{
		ret[index - 1] = malloc(sizeof(char) * (1 + 1
					+ ft_strlen(node->key) + ft_strlen(node->value)));
		if (ret[index - 1] == NULL)
			do_exit("ldpre_env_toenvp_f.malloc");
		ft_strlcpy(ret[index - 1], node->key, ft_strlen(node->key) + 1);
		ft_strlcat(ret[index - 1], "=", ft_strlen(ret[index - 1]) + 2);
		ft_strlcat(ret[index - 1], node->value,
			ft_strlen(ret[index - 1]) + ft_strlen(node->value) + 1);
		node = node->next;
	}
	ret[index - 1] = NULL;
	return (ret);
}
