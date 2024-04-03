/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:16:02 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/03 14:07:56 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	from < to
*/
static void	pull_two_token_back(t_token *htok_vec, int from, int to)
{
	const t_token	temp_token1 = htok_vec[from];
	const t_token	temp_token2 = htok_vec[from + 1];
	int				idx;

	idx = from - 1;
	while (++idx < to)
		htok_vec[idx] = htok_vec[idx + 2];
	htok_vec[to] = temp_token1;
	htok_vec[to + 1] = temp_token2;
}

/*
	to < from
*/
static void	pull_two_token_front(t_token *htok_vec, int from, int to)
{
	const t_token	temp_token1 = htok_vec[from];
	const t_token	temp_token2 = htok_vec[from + 1];
	int				idx;

	idx = from + 2;
	while (--idx > to + 1)
		htok_vec[idx] = htok_vec[idx - 2];
	htok_vec[to] = temp_token1;
	htok_vec[to + 1] = temp_token2;
}

static void	move_left_redirect(t_ft_vector *ptoken_stream)
{
	t_token	*htok_vec;
	size_t	to;
	size_t	idx;

	htok_vec = ptoken_stream->pbuffer;
	idx = -1;
	to = 0;
	while (++idx < ptoken_stream->size - 1)
	{
		if (to <= ptoken_stream->size - 2 && (htok_vec[idx].type == RDICT_READ
				|| htok_vec[idx].type == RDICT_HEREDOC))
		{
			if (htok_vec[idx + 1].type == IDENT)
				htok_vec[idx + 1].type = FILE_NAME;
			pull_two_token_front(htok_vec, idx, to);
			to += 2;
		}
		else if (htok_vec[idx].type == PIPE || htok_vec[idx].type == LPAR
			|| htok_vec[idx].type == RPAR || htok_vec[idx].type == OPRT_AND
			|| htok_vec[idx].type == OPRT_OR)
			to = idx + 1;
	}
}

static void	move_right_redirect(t_ft_vector *ptoken_stream)
{
	t_token	*htok_vec;
	int		to;
	int		idx;

	htok_vec = ptoken_stream->pbuffer;
	idx = ptoken_stream->size - 0;
	to = ptoken_stream->size - 2;
	while (--idx >= 0)
	{
		if (to >= 0 && (htok_vec[idx].type == RDICT_WRITE
				|| htok_vec[idx].type == RDICT_APPEND))
		{
			if (htok_vec[idx + 1].type == IDENT)
				htok_vec[idx + 1].type = FILE_NAME;
			pull_two_token_back(htok_vec, idx, to);
			to -= 2;
		}
		else if (htok_vec[idx].type == PIPE || htok_vec[idx].type == LPAR
			|| htok_vec[idx].type == RPAR || htok_vec[idx].type == OPRT_AND
			|| htok_vec[idx].type == OPRT_OR)
			to = idx - 2;
	}
}

void	move_redirection_token(t_ft_vector *ptoken_stream)
{
	size_t			idx;
	const t_token	*htok_vec = ptoken_stream->pbuffer;

	idx = -1;
	while (++idx < ptoken_stream->size - 1)
	{
		if ((htok_vec[idx].type == RDICT_APPEND
				|| htok_vec[idx].type == RDICT_WRITE
				|| htok_vec[idx].type == RDICT_HEREDOC
				|| htok_vec[idx].type == RDICT_READ)
			&& (htok_vec[idx + 1].type == PIPE
				|| htok_vec[idx + 1].type == LPAR
				|| htok_vec[idx + 1].type == RPAR
				|| htok_vec[idx + 1].type == OPRT_AND
				|| htok_vec[idx + 1].type == OPRT_OR))
			return ;
	}
	move_left_redirect(ptoken_stream);
	move_right_redirect(ptoken_stream);
}
