/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:03 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/14 02:42:55 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define STDIN_FD 0
# define STDOUT_FD 1

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

// import sig_atomic_t type
# include <signal.h>
volatile sig_atomic_t g_sigint = FALSE;

typedef enum e_exitcode
{
	SUCCESS = 0
}	t_exitcode;

// import flags for O_TRUNC, O_APPEND
# include <fcntl.h>
typedef enum e_filemode
{
	OUT_TRUNC = O_TRUNC,
	OUT_APPEND = O_APPEND,
	IN_OPEN = -1,
	IN_HEREDOC = -2
}	t_filemode;

typedef struct s_ld_redir_node
{
	struct s_ld_redir_node	*next;
	char					*filename;
	t_filemode				mode;
}	t_ld_redir_node;

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

- if any of the file creation or open fails, execution stops
- redirections will be handled in FIFO manner,
so the last redirection will only be written.
- to handle heredoc errors,
redirection should happen after heredoc is created.
*/
typedef struct s_ld_array_redir
{
	t_ld_redir_node	*stdin;
	t_ld_redir_node	*stdout;
}	t_ld_array_redir;

typedef struct s_ld_struct_exec
{
	t_ld_array_redir	redir;
	t_ld_array_pipe		pipe;
	char				*path;
	char				**argv;
	char				**envp;
}	t_ld_struct_exec;

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
