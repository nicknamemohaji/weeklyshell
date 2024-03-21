/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:54:44 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 17:39:55 by kyungjle         ###   ########.fr       */
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

void			ld_errno_file(char *trace, char *path);

// ld_chdir.c

t_bool			ld_chdir(char *path);

// do_exit.c

void			do_exit(char *errorstr);

// input_sighandler.c
# define OLDACT_SIGINT 0
# define OLDACT_SIGQUIT 1

void			input_sighandler_setup(struct sigaction oldacts[2]);
void			input_sighandler_restore(struct sigaction oldacts[2]);
void			input_sighandler(int sig, siginfo_t *info, void *ucontext);
void			ldexec_sigign_setup(struct sigaction oldacts[2]);

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

#endif
