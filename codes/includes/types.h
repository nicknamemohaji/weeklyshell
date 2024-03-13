/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:03 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/13 16:43:39 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef enum e_exitcode
{
	SUCCESS = 0
}	t_exitcode;

typedef struct s_node
{
	struct s_node	*next;
	void			*data;
}	t_node;

/*
pipes are created and closed in loader/preprocessor module.

- default value is -1, to express 'no pipes'
- preprocessor should evaluate error codes,
and close created pipe if needed.
*/
typedef struct s_ld_array_pipe
{
	int	stdin;
	int	stdout;
}	t_ld_array_pipe;

/*
redirections can occur multiple times, so store them in linked list.
node's content will be:
{
	t_node *next;
	char *data;		// this will contain path
}

- if any of the file creation or open fails, execution stops
- redirections will be handled in FIFO manner,
so the last redirection will only be written.
- to handle heredoc errors,
redirection should happen after heredoc is created.
*/
typedef struct s_ld_array_redir
{
	t_node	*stdin;
	t_node	*stdout;
}	t_ld_array_redir;

/*
environment variables are stored as map structure

helper functions:
- t_ld_map_env *ldpre_env_fromenvp_f(char **envp)
- char **ldpre_env_toenvp_f(t_ld_map_env *env)
- char *ldpre_env_fetch(char *key, t_ld_map_env *env)
- int ldpre_env_add(char *key, char *value, t_ld_map_env *env)
- int ldpre_env_remove(char *key, t_ld_map_env *env)
*/
typedef struct s_ld_map_node
{
	struct s_ld_map_node	*next;
	char					*key;
	char					*value;
}	t_ld_map_node;

typedef struct s_ld_map_env
{
	int				count;
	t_ld_map_node	*contents;
}	t_ld_map_env;

#endif
