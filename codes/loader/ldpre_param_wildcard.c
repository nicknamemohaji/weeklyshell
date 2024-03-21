/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:55:30 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 12:42:37 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		**ldpre_param_wildcard_f(char *arg);
static char	*get_prefix_f(char *s, char **ptr);
static void	match_prefix(char *prefix,
				t_ld_dir_node *node, t_ld_dir_node *prev);
static void	match_middle(char *pattern,
				t_ld_dir_node *node, t_ld_dir_node *prev);
static void	match_suffix(char *suffix,
				t_ld_dir_node *node, t_ld_dir_node *prev);

/*
Caller should free the returned pointer after use.
*/
char	**ldpre_param_wildcard_f(char *arg)
{
	t_ld_dir_node	start;
	char			*arg_ptr;
	char			*pattern;
	char			**ret;

	if (ft_strchr(arg, '*') == NULL)
		return (NULL);
	arg_ptr = arg;
	errno = 0;
	ldpre_param_wc_dirlist_f(&start);
	pattern = get_prefix_f(arg, &arg);
	match_prefix(pattern, start.next, &start);
	free(pattern);
	while (ft_strchr(arg, '*') != NULL)
	{
		pattern = get_prefix_f(arg, &arg);
		match_middle(pattern, start.next, &start);
		free(pattern);
	}
	match_suffix(arg, start.next, &start);
	ret = ldpre_param_wildcard_result_f(start.next);
	ldpre_param_wc_free_dirlist(start.next);
	free(arg_ptr);
	return (ret);
}

static char	*get_prefix_f(char *s, char **ptr)
{
	char	*ret;

	ret = s;
	while (*s != '*')
	{
		s += 1;
		*ptr += 1;
	}
	*ptr += 1;
	ret = ft_substr(ret, 0, s - ret);
	if (ret == NULL)
		do_exit("ldpre_param_wildcard.get_prefix_f.malloc");
	return (ret);
}

static void	match_prefix(char *prefix,
				t_ld_dir_node *node, t_ld_dir_node *prev)
{
	const size_t	pattern_len = ft_strlen(prefix);
	t_ld_dir_node	*node_ptr;

	if (pattern_len == 0)
		return ;
	while (node != NULL)
	{
		if (ft_strncmp(node->name_ptr, prefix, pattern_len) == 0)
		{
			prev = node;
			node = node->next;
		}
		else
		{
			node_ptr = node;
			prev->next = node->next;
			node = node->next;
			free(node_ptr->name);
			free(node_ptr);
		}
	}
}

static void	match_middle(char *pattern,
				t_ld_dir_node *node, t_ld_dir_node *prev)
{
	const size_t	pattern_len = ft_strlen(pattern);
	t_ld_dir_node	*node_ptr;

	if (pattern_len == 0)
		return ;
	while (node != NULL)
	{
		while (ft_strlen(node->name_ptr) >= pattern_len
			&& ft_strncmp(node->name_ptr, pattern, pattern_len) != 0)
			node->name_ptr++;
		if (ft_strncmp(node->name_ptr, pattern, pattern_len) == 0)
		{
			node->name_ptr += pattern_len;
			prev = node;
			node = node->next;
		}
		else
		{
			node_ptr = node;
			prev->next = node->next;
			node = node->next;
			free(node_ptr->name);
			free(node_ptr);
		}
	}
}

static void	match_suffix(char *suffix,
				t_ld_dir_node *node, t_ld_dir_node *prev)
{
	const size_t	pattern_len = ft_strlen(suffix);
	t_ld_dir_node	*node_ptr;

	if (pattern_len == 0)
		return ;
	while (node != NULL)
	{
		if (ft_strncmp(node->name_ptr + ft_strlen(node->name_ptr)
				- pattern_len, suffix, pattern_len) == 0)
		{
			prev = node;
			node = node->next;
		}
		else
		{
			node_ptr = node;
			prev->next = node->next;
			node = node->next;
			free(node_ptr->name);
			free(node_ptr);
		}
	}
}
