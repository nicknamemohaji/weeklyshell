/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:00 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/01 13:08:25 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include "types.h"
# include "utils.h"
# include "input.h"

// builtin/builtin_wrapper.c

pid_t	builtin_wrapper(t_ld_exec exec, t_ld_map_env *env);
t_bool	builtin_isbuiltin(char *name);

// loader/loader_wrapper.c

void	loader_wrapper(char *input, t_ld_map_env *env);

#endif
