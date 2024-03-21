/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:14 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 17:18:17 by kyungjle         ###   ########.fr       */
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

# define HEREDOC_MAX 4242

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

int		ldexec_run(t_ld_struct_exec exec);

// ldexec_heredoc.c

char	*ldexec_heredoc_assign_f(void);
t_bool	ldexec_heredoc(int fd, char *delim);

#endif
