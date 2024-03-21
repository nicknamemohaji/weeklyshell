/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_expansion2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:11:29 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 14:00:33 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		*ldpre_param_nodes_join_f(t_ld_param_node *node);
void		ldpre_param_nodes_free(t_ld_param_node *node);

/*
char	*ldpre_param_nodes_join_f(t_ld_param_node *node)
:param node: param nodes to join
:return: joined string

Joins param nodes into single string. Ignores NULL nodes.
Caller should free the returned pointer after use.
*/
char	*ldpre_param_nodes_join_f(t_ld_param_node *node)
{
	int				length;
	char			*ret;
	t_ld_param_node	*node_ptr;

	length = 0;
	node_ptr = node;
	while (node_ptr != NULL)
	{
		if (node_ptr->content != NULL)
			length += ft_strlen(node_ptr->content);
		node_ptr = node_ptr->next;
	}
	ret = ft_calloc(length + 1, sizeof(char));
	if (ret == NULL)
		do_exit("ldpre_param_nodes_join_f.malloc");
	while (node != NULL)
	{
		if (node->content != NULL)
		{
			ft_strlcat(ret, node->content,
				ft_strlen(ret) + ft_strlen(node->content) + 1);
		}
		node = node->next;
	}
	return (ret);
}

/*
void	ldpre_param_nodes_free(t_ld_param_node *node)
:param node: param nodes to free

Frees allocated param nodes
*/
void	ldpre_param_nodes_free(t_ld_param_node *node)
{
	t_ld_param_node	*node_ptr;

	while (node != NULL)
	{
		node_ptr = node;
		node = node->next;
		if (node_ptr->content != NULL)
			free(node_ptr->content);
		free(node_ptr);
	}
}
