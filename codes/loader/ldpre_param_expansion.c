/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:13:58 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 14:20:04 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char		*ldpre_param_expansion_f(char *arg, t_ld_map_env *env);
static char	*nodes_new_string_f(char *s, char **ptr);
static char	*nodes_new_expansion_f(char *s, char **ptr, t_ld_map_env *env);
static char	*nodes_new_expansion2_f(char *s, char **ptr, t_ld_map_env *env);

/*
char	*ldpre_param_expansion_f(char *arg, t_ld_map_env *env)
:param arg: raw string to expand
:param env: environement variables
:return: expanded string

Performs basic shell parameter expansion
- substitutes `$VAR` to value in map
- always expands given string, so don't call this function directly
	- quote removal function shoud check for single quote and call this
	- heredoc function should check delimiter and call this

Caller should free the returned pointer after use.
*/
char	*ldpre_param_expansion_f(char *arg, t_ld_map_env *env)
{
	t_ld_param_node	start;
	t_ld_param_node	*node;
	t_ld_param_node	*prev;
	char			*ret;
	char			*arg_ptr;

	arg_ptr = arg;
	start.next = NULL;
	prev = &start;
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

/*
static char	*nodes_new_string_f(char *s, char **ptr)
:param s: string to check
:param ptr: arg pointer of caller
:return: parsed string

Parses normal string(not environment variable) from given string s,
and moves caller's `arg` pointer to next character of parsed value
*/
static char	*nodes_new_string_f(char *s, char **ptr)
{
	char	*ret;
	char	*end_pos;

	end_pos = ft_strchr(s, '$');
	if (end_pos == NULL)
		end_pos = s + ft_strlen(s);
	*ptr = end_pos;
	ret = ft_substr(s, 0, end_pos - s);
	if (ret == NULL)
		do_exit("ldpre_param_expansion.nodes_new_string_f.malloc");
	return (ret);
}

/*
static char	*nodes_new_expansion_f(char *s, char **ptr, t_ld_map_env *env)
:param s: string to check
:param ptr: arg pointer of caller
:param env: environment variable map
:return: parsed string

Parses environment variable from given string s,
and moves caller's `arg` pointer to next character of parsed value.

Parsed environment variable key will be substituded to env value
- key parsing follows rule: [a-zA-Z_]{1}[0-9a-zA-Z_]+
	- exception: `$?`
- if key does not exist in environment, it will be substituded to null string
*/
static char	*nodes_new_expansion_f(char *s, char **ptr, t_ld_map_env *env)
{
	char	*ret;
	char	*end_pos;
	char	*key;

	end_pos = s;
	if (!(ft_isalpha(*end_pos) || *end_pos == '_'))
		return (nodes_new_expansion2_f(s, ptr, env));
	while (*end_pos != '\0' && (ft_isalnum(*end_pos) || *end_pos == '_'))
		end_pos++;
	*ptr = end_pos;
	key = ft_substr(s, 0, end_pos - s);
	if (key == NULL)
		do_exit("ldpre_param_expansion.nodes_new_expansion_f.malloc");
	ret = ldpre_env_fetch(key, env);
	free(key);
	if (ret != NULL)
	{
		ret = ft_strdup(ret);
		if (ret == NULL)
			do_exit("ldpre_param_expansion.nodes_new_expansion_f.malloc");
	}
	return (ret);
}

/*
static char	*nodes_new_expansion2_f(char *s, char **ptr, t_ld_map_env *env)
:param s: string to check
:param ptr: arg pointer of caller
:param env: environment variable map
:return: parsed string

Handles execiptional case when key is not valid - `$?`
*/
static char	*nodes_new_expansion2_f(char *s, char **ptr, t_ld_map_env *env)
{
	char	*ret;

	if (*s == '?')
	{
		*ptr += 2;
		ret = ldexec_env_exitcode_fetch_f(env);
	}
	else
		ret = ft_strdup("$");
	if (ret == NULL)
		do_exit("ldpre_param_expansion.nodes_new_expansion_f.malloc");
	return (ret);
}
