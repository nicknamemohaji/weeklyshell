/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:18:30 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 16:30:16 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		*ldpre_param_quote_f(char *arg,
				t_ld_map_env *env, t_bool *wildcard);
static char	*quote_removal_f(char *s,
				char **ptr, t_bool *wildcard, t_ld_map_env *env);

/*
char	*ldpre_param_quote_f(char *arg, t_ld_map_env *env, t_bool *wildcard)
:param arg: raw string to remove (and expand)
:param env: environment variables
:param wildcard: t_bool ptr of caller. if wildcard is NULL, than parameter
expansion is not executed.
:return: quote removed string

Performs quote removal. If needed, performs shell parmeter expansion.

- Caller should perform wildcard expansion if wildcard flag is set
- Caller should free the returned pointer after use.
*/
char	*ldpre_param_quote_f(char *arg, t_ld_map_env *env, t_bool *wildcard)
{
	t_ld_param_node	start;
	t_ld_param_node	*node;
	t_ld_param_node	*prev;
	char			*ret;
	char			*arg_ptr;

	if (wildcard != NULL)
		*wildcard = FALSE;
	arg_ptr = arg;
	start.next = NULL;
	prev = &start;
	while (*arg != '\0')
	{
		node = ft_calloc(1, sizeof(t_ld_param_node));
		if (node == NULL)
			do_exit("ldpre_param_expansion_f.malloc");
		node->content = quote_removal_f(arg, &arg, wildcard, env);
		node->next = NULL;
		prev->next = node;
		prev = node;
	}
	ret = ldpre_param_nodes_join_f(start.next);
	ldpre_param_nodes_free(start.next);
	free(arg_ptr);
	return (ret);
}

/*
static char	*quote_removal_f(char *s,
				char **ptr, t_bool *wildcard, t_ld_map_env *env)
:param s: arg
:param ptr: arg ptr of caller
:param wildcard: t_bool ptr of caller. if wildcard is NULL, than parameter
expansion is not executed.
:param env: environment variables
:return: parsed argument

Performs quote removal, and takes expansion if needed. If there is unquoted
`*`, marks the `wildcard` flag to take wildcard expansion after all strings
are unquoted.
*/
static char	*quote_removal_f(char *s,
				char **ptr, t_bool *wildcard, t_ld_map_env *env)
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
		if (ft_strchr(ret, '*') != NULL && wildcard != NULL)
			*wildcard = TRUE;
	}
	if (ret == NULL)
		do_exit("ldpre_param_quote.quote_removal_f.malloc");
	if (*s != '\'' && wildcard != NULL)
		ret = ldpre_param_expansion_f(ret, env);
	*ptr = end_ptr;
	return (ret);
}
