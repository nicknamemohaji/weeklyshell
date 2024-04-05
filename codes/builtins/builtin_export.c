/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:04:43 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/05 15:19:43 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int				builtin_export(char *args[], t_ld_map_env *env);
static int		builtin_export_print(t_ld_map_env *env);
static t_bool	cmp(const void *c1, const void *c2);


int	builtin_export(char *args[], t_ld_map_env *env)
{
	int		i;
	char	*key;
	char	*value;

	if (args[1] == NULL)
		return (builtin_export_print(env));
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			key = ft_strdup(args[i]);
			value = ft_strdup("");
		}
		else
		{
			key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			value = ft_strdup(ft_strchr(args[i], '=') + 1);
		}
		if (key == NULL || value == NULL)
			do_exit("builtin_export.malloc");
		ldpre_env_add(key, value, env);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	builtin_export_print(t_ld_map_env *env)
{
	char	**envp;

	envp = ldpre_env_toenvp_f(env);
	ft_qsort((void **)envp, 0, env->count - 1, cmp);
	for (int i = 0; envp[i] != NULL; i++)
		printf("%s\n", envp[i]);
	free_ft_split(envp);
	return (EXIT_SUCCESS);
}

static t_bool	cmp(const void *c1, const void *c2)
{
	unsigned char	*c1_ptr;
	unsigned char	*c2_ptr;

	if (c1 == c2)
		return (FALSE);
	c1_ptr = (unsigned char *) c1;
	c2_ptr = (unsigned char *) c2;
	while (*c1_ptr != '=' && *c2_ptr != '=')
	{
		if (*c1_ptr != *c2_ptr)
			break ;
		c1_ptr++;
		c2_ptr++;
	}
	if (*c1_ptr == '=')
		c1_ptr = (unsigned char *)"\0";
	if (*c2_ptr == '=')
		c2_ptr = (unsigned char *)"\0";
	return (*c1_ptr < *c2_ptr);
}
