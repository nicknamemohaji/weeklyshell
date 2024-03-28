/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:11:14 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 12:49:03 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "lexer.h"

static void	skip_whitespace(t_lexer *plexer)
{
	while (plexer->cur_ptr < plexer->input_size
		&& ft_isspace(plexer->input[plexer->cur_ptr]))
		plexer->cur_ptr++;
	plexer->next_ptr = plexer->cur_ptr + 1;
}

/*
	allocator for token in ft_vector

	pt : adress for token in vector
	plexer : parameter to get token, pointer to lexer
*/
int	get_next_token(t_token *pt, t_lexer *plexer)
{
	*pt = construct_token(get_token_type(plexer));
	if (LPAR <= pt->type && pt->type <= RDICT_WRITE)
	{
		pt->field.push_back(pt, plexer->input[plexer->cur_ptr]);
		plexer->cur_ptr++;
		plexer->next_ptr++;
	}
	else if (OPRT_AND <= pt->type && pt->type <= RDICT_APPEND)
	{
		pt->field.push_back(pt, plexer->input[plexer->cur_ptr]);
		pt->field.push_back(pt, plexer->input[plexer->next_ptr]);
		plexer->cur_ptr += 2;
		plexer->next_ptr += 2;
	}
	else if (KEY_ECHO <= pt->type && pt->type <= KEY_EXIT)
		get_keyword(plexer, pt);
	else if (pt->type == IDENT)
		get_ident(plexer, pt);
	else
		plexer->cur_ptr++;
	plexer->next_ptr = plexer->cur_ptr + 1;
	return (1);
}

// token_stream을 token*의 벡터로 만들까...
t_ft_vector	tokenize(const char *cstr)
{
	t_ft_vector	token_stream;
	t_lexer		*plexer;

	token_stream = construct_ftvec(get_next_token, destruct_token,
			sizeof(t_token));
	plexer = (t_lexer *)malloc(sizeof(t_lexer));
	plexer->input = cstr;
	plexer->input_size = ft_strlen(cstr);
	plexer->cur_ptr = 0;
	plexer->next_ptr = 1;
	skip_whitespace(plexer);
	while (plexer->cur_ptr < plexer->input_size)
	{
		token_stream.push_back(&token_stream, plexer);
		skip_whitespace(plexer);
	}
	free(plexer);
	return (token_stream);
}
