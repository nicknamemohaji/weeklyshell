/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:15:32 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:17:51 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "lexer.h"

int	is_letter(const char c)
{
	return (!ft_isspace(c) && c != '&' && c != '|' && c != ';' && c != '<'
		&& c != '>' && c != '(' && c != ')');
}

int	get_ident(t_lexer *plexer, t_token *ptoken)
{
	int	flag;

	flag = 0;
	while (plexer->cur_ptr < plexer->input_size)
	{
		if (!flag && (plexer->input[plexer->cur_ptr] == '\''
				|| plexer->input[plexer->cur_ptr] == '\"'))
			flag = plexer->input[plexer->cur_ptr];
		else if (flag && plexer->input[plexer->cur_ptr] == flag)
			flag = 0;
		else if (!flag && !is_letter(plexer->input[plexer->cur_ptr]))
			break ;
		ptoken->field.push_back(&ptoken->field, plexer->input[plexer->cur_ptr]);
		plexer->cur_ptr++;
	}
	plexer->next_ptr = plexer->cur_ptr + 1;
	return (1);
}

int	get_keyword(t_lexer *plexer, t_token *ptoken)
{
	ptoken->field.clear(&ptoken->field);
	if (ptoken->type == KEY_ECHO)
		ptoken->field.append(&ptoken->field, "echo");
	else if (ptoken->type == KEY_CD)
		ptoken->field.append(&ptoken->field, "cd");
	else if (ptoken->type == KEY_ENV)
		ptoken->field.append(&ptoken->field, "env");
	else if (ptoken->type == KEY_EXPORT)
		ptoken->field.append(&ptoken->field, "export");
	else if (ptoken->type == KEY_EXIT)
		ptoken->field.append(&ptoken->field, "exit");
	else if (ptoken->type == KEY_PWD)
		ptoken->field.append(&ptoken->field, "pwd");
	else if (ptoken->type == KEY_UNSET)
		ptoken->field.append(&ptoken->field, "unset");
	plexer->cur_ptr += ptoken->field.size;
	plexer->next_ptr = plexer->cur_ptr + 1;
	return (1);
}
