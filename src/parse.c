/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:08:56 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/08 22:26:17 by dogwak           ###   ########.fr       */
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

static int	syntax_check(t_ft_vector *ptoken_stream)
{
	const t_token	*htok_vec = ptoken_stream->pbuffer;
	size_t			idx;

	idx = -1;
	while (++idx < ptoken_stream->size - 1)
	{
		if ((htok_vec[idx].type == RDICT_READ
				|| htok_vec[idx].type == RDICT_WRITE
				|| htok_vec[idx].type == RDICT_APPEND
				|| htok_vec[idx].type == RDICT_HEREDOC)
			&& htok_vec[idx + 1].type != FILE_NAME)
			return (0);
	}
	return (1);
}

t_ast_node	*syntax_error(t_ft_vector *ptoken_stream)
{
	write(2, "Syntax Error.\n", 14);
	delete_ftvec(ptoken_stream);
	return (NULL);
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
	if (ptoken_stream->push_back(ptoken_stream, NULL) == 0)
	{
		delete_ftvec(ptoken_stream);
		return (ast_malloc_error(NULL));
	}
	if (!syntax_check(ptoken_stream))
		return (syntax_error(ptoken_stream));
	p = new_parser(ptoken_stream);
	if (p == NULL)
		return (ast_malloc_error(NULL));
	else
		tree = parse_expression(p, P_LOWEST);
	delete_ftvec(ptoken_stream);
	delete_parser(p);
	return (tree);
}
