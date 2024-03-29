/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:08:56 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/29 19:13:28 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	construct_end_token(void *pos, void *ptoken)
{
	((t_token *)pos)->type = END;
	((t_token *)pos)->field.pbuffer = NULL;
	ptoken++;
	return (1);
}

/*
	input : pointer of token stream, result of lexing.
	result : root node of abstract syntax tree.

	return NULL if syntax error.
*/
t_ast_node	*parse(t_ft_vector *ptoken_stream)
{
	t_parser	*p;
	t_ast_node	*tree;

	move_redirection_token(ptoken_stream);
	ptoken_stream->construct_data = construct_end_token;
	ptoken_stream->push_back(ptoken_stream, NULL);
	p = new_parser(ptoken_stream);
	tree = parse_expression(p, P_LOWEST);
	delete_parser(p);
	return (tree);
}
