/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:13:58 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/20 23:50:26 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		*ldpre_param_expansion_f(char *arg, t_ld_map_env *env);
static char	*nodes_new_string_f(char *s, char **ptr);
static char	*nodes_new_expansion_f(char *s, char **ptr, t_ld_map_env *env);
char		*ldpre_param_nodes_join_f(t_ld_param_node *node);
void		ldpre_param_nodes_free(t_ld_param_node *node);

char	*ldpre_param_expansion_f(char *arg, t_ld_map_env *env)
{
	t_ld_param_node	start;
	t_ld_param_node	*node;
	t_ld_param_node	*prev;
	char			*ret;
	char			*arg_ptr;

	arg_ptr = arg;
	start.next = NULL;
	prev = &(start);
	while (*arg != '\0')
	{
		node = ft_calloc(1, sizeof(t_ld_param_node));
		if (node == NULL)
			do_exit("ldpre_param_expansion_f.malloc");
		if (*arg == '$')
			node->content = nodes_new_expansion_f(++arg, &arg, env);
		else
			node->content = nodes_new_string_f(arg, &arg);
		prev->next = node;
		prev = node;
	}
	ret = ldpre_param_nodes_join_f(start.next);
	ldpre_param_nodes_free(start.next);
	free(arg_ptr);
	return (ret);
}

static char	*nodes_new_string_f(char *s, char **ptr)
{
	char	*ret;
	char	*end_pos;

	end_pos = ft_strchr(s, '$');
	if (end_pos == NULL)
		end_pos = s + ft_strlen(s);
	ret = ft_substr(s, 0, end_pos - s);
	if (ret == NULL)
		do_exit("ldpre_param_expansion.nodes_new_string_f.malloc");
	*ptr = end_pos;
	return (ret);
}

static char	*nodes_new_expansion_f(char *s, char **ptr, t_ld_map_env *env)
{
	char	*ret;
	char	*end_pos;
	char	*key;

	end_pos = s;
	if (!(ft_isalpha(*end_pos) || *end_pos == '_'))
	{
		*ptr += 2;
		return (NULL);
	}
	while (*end_pos != '\0' && (ft_isalnum(*end_pos) || *end_pos == '_'))
		end_pos++;
	*ptr = end_pos;
	key = ft_substr(s, 0, end_pos - s);
	ret = ldpre_env_fetch(key, env);
	free(key);
	if (ret != NULL)
		ret = ft_strdup(ret);
	return (ret);
}

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
		do_exit("ldpre_param_expansion.ldpre_param_nodes_join_f.malloc");
	while (node != NULL)
	{
		if (node->content != NULL)
			ft_strlcat(ret, node->content,
				ft_strlen(ret) + ft_strlen(node->content) + 1);
		node = node->next;
	}
	return (ret);
}

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
