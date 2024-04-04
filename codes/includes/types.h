/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:03 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/04 17:59:00 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

// import sig_atomic_t type
# include <signal.h>

// ANSI terminal contrl characters
# define TERM_COLOR_END "\001\033[m\002"
# define TERM_COLOR_RED "\001\033[31m\002"
# define TERM_COLOR_GREEN "\001\033[32m\002"
# define TERM_COLOR_YELLOW "\001\033[33m\002"
# define TERM_COLOR_BLUE "\001\033[34m\002"

# define STDIN_FD 0
# define STDOUT_FD 1

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

extern volatile sig_atomic_t	g_sigint;

// used by loader.preprocessor.ast
typedef struct s_ld_heredoc
{
	char	*heredoc_name;
	int		stdin_fd;
}	t_ld_heredoc;

// used by loader.preprocessor.param.expansion
typedef struct s_ld_param_node
{
	char					*content;
	struct s_ld_param_node	*next;
}	t_ld_param_node;

// used by loader.preprocessor.param.wildcard
typedef struct s_ld_dir_node
{
	char					*name;
	char					*name_ptr;
	struct s_ld_dir_node	*next;
}	t_ld_dir_node;

// used by loader.executor
typedef struct s_ld_exec
{
	char				*path;
	char				**argv;
	char				**envp;
}	t_ld_exec;

/*
used by loader.executor

commands connected to pipes are spawned concurrently,
so store them in linked list.
*/
typedef struct s_ld_exec_nodes
{
	t_ld_exec				exec;
	pid_t					pid;
	int						exitcode;
	struct s_ld_exec_nodes	*next;
}	t_ld_exec_nodes;

/*
used by loader.preprocessor.environment

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
