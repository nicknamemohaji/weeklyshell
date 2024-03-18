/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_map_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:09:12 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/19 02:02:30 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"

t_ld_map_env	*ldpre_env_fromenvp_f(char **envp);
void			ld_map_node_attach(t_ld_map_env *map, t_ld_map_node *node);
char			**ldpre_env_toenvp_f(t_ld_map_env *map);
void			free_ld_map(t_ld_map_env *map);

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
		printf("envp %s\n", *envp);
		ld_map_node_attach(ret, node);
		node->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp + 1);
		node->value = ft_substr(*envp, ft_strlen(node->key), ft_strlen(*envp));
		envp++;
		count++;
	}
	ret->count = count;
	return (ret);
}

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

char	**ldpre_env_toenvp_f(t_ld_map_env *map)
{
	int				index;
	char			**ret;
	t_ld_map_node	*node;

	ret = malloc(sizeof(char *) * (map->count + 1));
	if (ret == NULL)
		do_exit("ldpre_env_toenvp_f.malloc");
	index = -1;
	node = map->contents;
	while (++index < map->count)
	{
		ret[index] = malloc(sizeof(char) * (1 + 1
					+ ft_strlen(node->key) + ft_strlen(node->value)));
		if (ret == NULL)
			do_exit("ldpre_env_toenvp_f.malloc");
		ft_strlcpy(ret[index], node->key, ft_strlen(node->key) + 1);
		ft_strlcpy(ret[index], "=", 1 + 1);
		ft_strlcat(ret[index], node->value,
			ft_strlen(ret[index]) + ft_strlen(node->value) + 1);
		node = node->next;
	}
	ret[index] = NULL;
	return (ret);
}
