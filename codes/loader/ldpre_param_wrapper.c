/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:34:01 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/01 15:10:58 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		**ldpre_param_wrapper_f(char **argv, t_ld_map_env *env);
static void	split_argv(char **argv, t_ld_param_node *start, t_ld_map_env *env);
static void	argv_wildcard(char *arg, t_ld_param_node *start, t_ld_map_env *env);

char	**ldpre_param_wrapper_f(char **argv, t_ld_map_env *env)
{
	t_ld_param_node	start;
	t_ld_param_node	*node;
	int				count;
	char			**ret;

	split_argv(argv, &start, env);
	free_ft_split(argv);
	node = start.next;
	count = 0;
	while (node != NULL)
	{
		count += 1;
		node = node->next;
	}
	ret = ft_calloc(count + 1, sizeof(char *));
	argv = ret;
	node = start.next;
	while (node != NULL)
	{
		*(argv++) = node->content;
		start.next = node;
		node = node->next;
		free(start.next);
	}
	return (ret);
}

static void	split_argv(char **argv, t_ld_param_node *start, t_ld_map_env *env)
{
	t_ld_param_node	*node;
	t_bool			wildcard;

	while (*argv != NULL)
	{
		node = malloc(1 * sizeof(t_ld_param_node));
		if (node == NULL)
			do_exit("ldpre_param_wrapper.split_argv.malloc");
		node->next = NULL;
		node->content = ft_strdup(*argv);
		if (node->content == NULL)
			do_exit("ldpre_param_wrapper.split_argv.malloc");	
		node->content = ldpre_param_quote_f(node->content, env, &wildcard);
		if (wildcard)
		{
			argv_wildcard(node->content, start, env);
			free(node);
		}
		else
		{
			start->next = node;
			start = node;		
		}
		argv += 1;
	}
}

static void	argv_wildcard(char *arg, t_ld_param_node *start, t_ld_map_env *env)
{
	char			**wildcard_expansion;

	wildcard_expansion = ldpre_param_wildcard_f(arg);
	split_argv(wildcard_expansion, start, env);
	free_ft_split(wildcard_expansion);
}
