#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "types.h"
# include "libft.h"

int     builtin_cd(char *args[], t_ld_map_env *env);
int     builtin_pwd(char *args[], t_ld_map_env *env);
int     builtin_echo(char *args[], t_ld_map_env *env);
int     builtin_exit(char *args[], t_ld_map_env *env);
int     builtin_export(char *args[], t_ld_map_env *env);
int     builtin_unset(char *args[], t_ld_map_env *env);
int     builtin_wrapper(t_ld_struct_exec exec, t_ld_map_env *env);
t_bool  builtin_isbuiltin(char *name);

#endif
