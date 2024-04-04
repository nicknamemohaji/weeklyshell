/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:18 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/31 16:50:50 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "parser.h"

int	construct_token_ptr(void *pos, void *param)
{
	t_token	**target_pos;

	target_pos = pos;
	*target_pos = (t_token *)param;
	return (1);
}

void	destruct_token_ptr(void *self)
{
	self++;
}

static t_ast_node	*new_ast_command_node(t_ft_vector *ptok_ptr_vec)
{
	t_ast_node	*command;
	t_token		**h_tok_ptr_vec;
	size_t		idx;

	h_tok_ptr_vec = ptok_ptr_vec->pbuffer;
	command = new_ast_node();
	if (command == NULL)
		return (ast_malloc_error(NULL));
	command->node_type = NODE_COMMAND;
	command->pcmd = new_cmd_list(ptok_ptr_vec->size);
	if (command->pcmd == NULL)
		return (ast_malloc_error(command));
	idx = -1;
	while (++idx < ptok_ptr_vec->size)
	{
		command->pcmd[idx]
			= ft_strdup(h_tok_ptr_vec[idx]
				->field.c_str(&h_tok_ptr_vec[idx]->field));
		if (command->pcmd[idx] == NULL)
			return (ast_malloc_error(command));
	}
	return (command);
}

/*
	push_back until parser meet the operator token
*/
t_ast_node	*parse_command(t_parser *self)
{
	t_ast_node	*command;
	t_ft_vector	token_ptr_vec;
	int			next_node_type;

	token_ptr_vec = construct_ftvec(construct_token_ptr, destruct_token_ptr,
			sizeof(t_token *));
	if (token_ptr_vec.pbuffer == NULL)
		return (ast_malloc_error(NULL));
	while (1)
	{
		if (!token_ptr_vec.push_back(&token_ptr_vec, self->pcur_token))
			return (ast_malloc_error(NULL));
		next_node_type = get_prefix_node_type(self->pnext_token->type);
		if (next_node_type != NODE_WORD)
			break ;
		move_next_token(self);
	}
	command = new_ast_command_node(&token_ptr_vec);
	destruct_ftvec(&token_ptr_vec);
	return (command);
}
