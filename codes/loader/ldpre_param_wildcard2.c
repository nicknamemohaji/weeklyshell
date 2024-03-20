/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_param_wildcard2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:00:50 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 00:24:49 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

void		ldpre_param_wc_dirlist_f(t_ld_dir_node *start);
void		ldpre_param_wc_free_dirlist(t_ld_dir_node *node);
char		**ldpre_param_wildcard_result(t_ld_dir_node *node);
static int	dirlist_length(t_ld_dir_node *node);

void	ldpre_param_wc_free_dirlist(t_ld_dir_node *node)
{
	t_ld_dir_node	*ptr;

	while (node != NULL)
	{
		ptr = node;
		node = node->next;
		free(ptr->name);
		free(ptr);
	}
}

void	ldpre_param_wc_dirlist_f(t_ld_dir_node *prev)
{
	DIR				*dir;
	struct dirent	*ent;
	t_ld_dir_node	*node;

	dir = opendir(".");
	if (dir == NULL)
		do_exit("ldpre_param_wc_dirlist_f.opendir");
	ent = readdir(dir);
	while (ent != NULL)
	{
		node = ft_calloc(1, sizeof(t_ld_dir_node));
		if (node == NULL)
			do_exit("ldpre_param_wc_dirlist_f.malloc");
		node->name = ft_strdup(ent->d_name);
		if (node->name == NULL)
			do_exit("ldpre_param_wc_dirlist_f.malloc");
		node->name_ptr = node->name;
		prev->next = node;
		prev = node;
		ent = readdir(dir);
	}
	if (errno != 0)
		do_exit("ldpre_param_wc_dirlist_f.readdir");
	if (closedir(dir) != 0)
		do_exit("ldpre_param_wc_dirlist_f.closedir");
}

char	**ldpre_param_wildcard_result(t_ld_dir_node *node)
{
	int				count;
	char			**ret;

	ret = malloc((dirlist_length(node) + 1) * sizeof(char *));
	if (ret == NULL)
		do_exit("ldpre_param_wildcard_result.malloc");
	count = 0;
	while (node != NULL)
	{
		ret[count] = ft_strdup(node->name);
		if (ret[count] == NULL)
			do_exit("ldpre_param_wildcard_result.malloc");
		count += 1;
		node = node->next;
	}
	ret[count] = NULL;
	return (ret);
}

static int	dirlist_length(t_ld_dir_node *node)
{
	int	count;

	count = 0;
	while (node != NULL)
	{
		count += 1;
		node = node->next;
	}
	return (count);
}
