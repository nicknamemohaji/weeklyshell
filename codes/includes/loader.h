/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:14 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 15:50:43 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"
# include "types.h"
# include "parser.h"

# define HEREDOC_MAX 4242

// ldpre_param_wrapper.c

char	**ldpre_param_wrapper_f(char **argv, t_ld_map_env *env);

// ldpre_param_expansion.c

char	*ldpre_param_expansion_f(char *arg, t_ld_map_env *env);

// ldpre_param_expansion2.c

char	*ldpre_param_nodes_join_f(t_ld_param_node *node);
void	ldpre_param_nodes_free(t_ld_param_node *node);

// ldpre_param_quote.c

char	*ldpre_param_quote_f(char *arg, t_ld_map_env *env, t_bool *wildcard);

// ldpre_param_wildcard.c

char	**ldpre_param_wildcard_f(char *arg);

// ldpre_param_wildcard2.c

void	ldpre_param_wc_dirlist_f(t_ld_dir_node *start);
void	ldpre_param_wc_free_dirlist(t_ld_dir_node *node);
char	**ldpre_param_wildcard_result_f(t_ld_dir_node *node);

// ldexec_env_exitcode.c

char	*ldexec_env_exitcode_fetch_f(t_ld_map_env *env);
void	ldexec_env_exitcode_update(int code, t_ld_map_env *env);

// ldexec_findexec.c

char	*ldexec_exec_find_f(char *cmd, t_bool *need_free, const char *path);

// ldexec_run.c

pid_t	ldexec_run_bin(t_ld_exec exec, pid_t pid);
void	ldexec_select_type(t_ld_exec exec, t_ld_exec_nodes *node,
			t_ld_map_env *env, pid_t pid);

// ldpre_ast.c

int		ldpre_ast(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_subshell.c

int		ldpre_ast_subshell(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_pipe.c

int		ldpre_ast_pipe(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_logical.c

int		ldpre_ast_and(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
int		ldpre_ast_or(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_redir.c

int		ldpre_ast_wopen(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
int		ldpre_ast_ropen(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);
int		ldpre_ast_wpopen(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_redir2.c

t_bool	ldpre_ast_redir_outfile(char *filename, enum e_node_type mode);
t_bool	ldpre_ast_redir_infile(char *filename, t_ld_heredoc *heredoc,
			enum e_node_type mode, t_ld_map_env *env);

// ldpre_ast_redir_heredoc.c

char	*ldexec_heredoc_assign_f(void);
t_bool	ldexec_heredoc(int fd, char *delim,
			t_bool expansion, t_ld_map_env *env);

// ldpre_heredoc_vector.c

int		construct_heredoc_name(void *pos, void *param);
void	destruct_heredoc_name(void *pos);

// ldpre_ast_exec.c

int		ldpre_ast_exec(t_ast_node *ast, t_ld_map_env *env,
			t_ld_exec_nodes *exec, t_ld_heredoc *heredoc);

// ldpre_ast_exec_execall.c

int		exec_cleanup(t_ld_exec_nodes *node,
			t_ld_map_env *env, t_bool free_flag);

#endif
