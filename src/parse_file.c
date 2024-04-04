/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:35:55 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/03 14:52:10 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "parser.h"

// get single word as a file node
t_ast_node	*parse_file(t_parser *self)
{
	t_ast_node	*file;

	if ((size_t)self->cur_idx == self->ptoken_stream->size)
		return (ast_syntax_error(NULL));
	file = new_ast_node();
	if (file == NULL)
		return (ast_malloc_error(file));
	file->node_type = get_prefix_node_type(self->pcur_token->type);
	if (file->node_type != NODE_FILE)
		return (ast_syntax_error(file));
	file->node_type = NODE_FILE;
	file->pcmd = new_cmd_list(1);
	file->pcmd[0]
		= ft_strdup(self->pcur_token->field.c_str(&self->pcur_token->field));
	return (file);
}
