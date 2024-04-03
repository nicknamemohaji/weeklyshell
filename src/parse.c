/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:08:56 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/03 14:43:10 by dogwak           ###   ########.fr       */
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
	input : c type, NULL terminating string. input of shell.
	result : root node of abstract syntax tree.

	return NULL if syntax or system error.
*/
t_ast_node	*parse(const char *cstr)
{
	t_ft_vector	*ptoken_stream;
	t_parser	*p;
	t_ast_node	*tree;

	ptoken_stream = tokenize(cstr);
	if (ptoken_stream == NULL)
		return (ast_malloc_error(NULL));
	move_redirection_token(ptoken_stream);
	ptoken_stream->construct_data = construct_end_token;
	p = new_parser(ptoken_stream);
	if (ptoken_stream->push_back(ptoken_stream, NULL) == 0 || p == NULL)
	{
		delete_ftvec(ptoken_stream);
		delete_parser(p);
		return (ast_malloc_error(NULL));
	}
	tree = parse_expression(p, P_LOWEST);
	delete_ftvec(ptoken_stream);
	delete_parser(p);
	return (tree);
}
