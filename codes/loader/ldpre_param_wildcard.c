/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:55:30 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 17:17:38 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		**ldpre_param_wildcard_f(char *arg);
static char	*get_pattern_f(char *s, char **ptr);
static void	match_prefix(char *prefix,
				t_ld_dir_node *node, t_ld_dir_node *prev);
static void	match_middle(char *pattern,
				t_ld_dir_node *node, t_ld_dir_node *prev);
static void	match_suffix(char *suffix,
				t_ld_dir_node *node, t_ld_dir_node *prev);

/*
char	**ldpre_param_wildcard_f(char *arg)
:param arg: string after quote removal (+ shell param expansion)
:return: array of strings containing each match

- Caller should expand argument array, adding returned contents
- Caller should free the returned pointer after use
	(use free_ft_split function)
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
	pattern = get_pattern_f(arg, &arg);
	match_prefix(pattern, start.next, &start);
	free(pattern);
	while (ft_strchr(arg, '*') != NULL)
	{
		pattern = get_pattern_f(arg, &arg);
		match_middle(pattern, start.next, &start);
		free(pattern);
	}
	match_suffix(arg, start.next, &start);
	ret = ldpre_param_wildcard_result_f(start.next);
	ldpre_param_wc_free_dirlist(start.next);
	free(arg_ptr);
	return (ret);
}

/*
static char	*get_pattern_f(char *s, char **ptr)
:param s: arg
:param ptr: arg ptr of caller
:return: parsed pattern

Caller's arg ptr will be moved to next `*`, allowing to run
match_middle function until no `*` is found.
*/
static char	*get_pattern_f(char *s, char **ptr)
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
		do_exit("ldpre_param_wildcard.get_pattern_f.malloc");
	return (ret);
}

/*
static void	match_prefix(char *prefix,
				t_ld_dir_node *node, t_ld_dir_node *prev)
:param prefix: pattern to match
:param node: pointer to first node
:param prev: pointer to root node

Strictly match prefix pattern. Free all nodes that does not match
*/
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

/*
static void	match_middle(char *pattern,
				t_ld_dir_node *node, t_ld_dir_node *prev)
:param pattern: pattern to match
:param node: pointer to first node
:param prev: pointer to root node

Match middle patterns, more generously :). Free all nodes that does not match
*/
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

/*
static void	match_suffix(char *suffix,
				t_ld_dir_node *node, t_ld_dir_node *prev)
:param suffix: pattern to match
:param node: pointer to first node
:param prev: pointer to root node

Strictly match suffix pattern. Free all nodes that does not match
*/
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
