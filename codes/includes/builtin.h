/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:05:01 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/15 15:05:08 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "types.h"
# include "libft.h"

// builtin_cd.c

int		builtin_cd(char *args[], t_ld_map_env *env);

// builtin_pwd.c

int		builtin_pwd(char *args[], t_ld_map_env *env);

// builtin_echo.c

int		builtin_echo(char *args[], t_ld_map_env *env);

// builtin_exit.c

int		builtin_exit(char *args[], t_ld_map_env *env);
t_bool	builtin_check_argument_count(const char *args[], int limit, char *cmd);

// builtin_export.c

int		builtin_export(char *args[], t_ld_map_env *env);

// builtin_unset.c

int		builtin_unset(char *args[], t_ld_map_env *env);

// builtin_env.c

int		builtin_env(char *args[], t_ld_map_env *env);

#endif
