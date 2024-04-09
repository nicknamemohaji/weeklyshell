/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:54:44 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 15:18:07 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>

# include "libft.h"
# include "types.h"

// free_ft_split.c

void			free_ft_split(char **ptr);

// ld_errno_file.c

t_bool			ld_errno_file(const char *trace, char *path);

// ld_chdir.c

t_bool			ld_chdir(const char *trace, char *path);

// do_exit.c

void			do_exit(const char *errorstr);

// do_getcwd.c

char			*do_getcwd_f(char *buf, size_t size);

// ld_map_functions.c

t_ld_map_env	*ldpre_env_fromenvp_f(char **envp);
void			ld_map_node_attach(t_ld_map_env *map, t_ld_map_node *node);
char			**ldpre_env_toenvp_f(t_ld_map_env *map);
void			free_ld_map(t_ld_map_env *map);

// ld_map_functions2.c

char			*ldpre_env_fetch(char *key, t_ld_map_env *map);
void			ldpre_env_add(char *key, char *value, t_ld_map_env *map);
t_bool			ldpre_env_remove(char *key, t_ld_map_env *map);
t_ld_map_node	**ldpre_env_searchkey(char *key, t_ld_map_env *map);
t_bool			ldpre_env_validate_key(char *key);

// ft_qsort.c
void			ft_qsort(void **arr, int left, int right,
					t_bool (*cmp)(const void*, const void*));

#endif
