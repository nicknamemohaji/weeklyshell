/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:28:04 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 12:47:03 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	construct_token(int token_type)
{
	t_token	t;

	t.type = token_type;
	t.field = construct_ftstr();
	return (t);
}

void	destruct_token(t_token *this)
{
	destruct_ftstr(&this->field);
}
