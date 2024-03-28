/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:55:27 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:21:35 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_ast_node	*new_ast_node(void)
{
	t_ast_node	*pnode;

	pnode = (t_ast_node *)malloc(sizeof(t_ast_node));
	pnode->pcmd = NULL;
	pnode->left = NULL;
	pnode->right = NULL;
	return (pnode);
}

void	delete_ast_node(t_ast_node *self)
{
	if (self == NULL)
		return ;
	if (self->left != NULL)
		delete_ast_node(self->left);
	if (self->right != NULL)
		delete_ast_node(self->right);
	free(self->pcmd);
	free(self);
}
