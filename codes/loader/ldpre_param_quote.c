/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:18:30 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 12:42:29 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		*ldpre_param_quote_f(char *arg, t_ld_map_env *env);
static char	*quote_removal_f(char *s, char **ptr, t_ld_map_env *env);

/*
Caller should free the returned pointer after use.
*/
char	*ldpre_param_quote_f(char *arg, t_ld_map_env *env)
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
		node = malloc(1 * sizeof(t_ld_param_node));
		if (node == NULL)
			do_exit("ldpre_param_expansion_f.malloc");
		node->content = quote_removal_f(arg, &arg, env);
		node->next = NULL;
		prev->next = node;
		prev = node;
	}
	ret = ldpre_param_nodes_join_f(start.next);
	ldpre_param_nodes_free(start.next);
	free(arg_ptr);
	return (ret);
}

static char	*quote_removal_f(char *s, char **ptr, t_ld_map_env *env)
{
	char	*ret;
	char	*end_ptr;

	if (*s == '\"' || *s == '\'')
	{
		end_ptr = ft_strchr(s + 1, *s);
		ret = ft_substr(s, 1, end_ptr++ - s - 1);
	}
	else
	{
		end_ptr = s;
		while (*end_ptr != '\0' && *end_ptr != '\'' && *end_ptr != '\"')
			end_ptr++;
		ret = ft_substr(s, 0, end_ptr - s);
	}
	if (ret == NULL)
		do_exit("ldpre_param_quote.quote_removal_f.malloc");
	if (*s != '\'')
	{
		ret = ldpre_param_expansion_f(ret, env);
		if (ret == NULL)
			do_exit("ldpre_param_quote.quote_removal_f.malloc");
	}
	*ptr = end_ptr;
	return (ret);
}
