/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:19:50 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:19:58 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "lexer.h"

static int	get_token_type2(t_lexer *plexer, const char *pc)
{
	if (*pc == '&' && *(pc + 1) == '&')
		return (OPRT_AND);
	else if (ft_strncmp(pc, "echo", 4) == 0 && ft_isspace(*(pc + 4)))
		return (KEY_ECHO);
	else if (ft_strncmp(pc, "env", 3) == 0 && ft_isspace(*(pc + 3)))
		return (KEY_ENV);
	else if (ft_strncmp(pc, "unset", 5) == 0 && ft_isspace(*(pc + 5)))
		return (KEY_UNSET);
	else if (ft_strncmp(pc, "exit", 4) == 0 && ft_isspace(*(pc + 4)))
		return (KEY_EXIT);
	else if (ft_strncmp(pc, "export", 6) == 0 && ft_isspace(*(pc + 6)))
		return (KEY_EXPORT);
	else if (ft_strncmp(pc, "cd", 2) == 0 && ft_isspace(*(pc + 2)))
		return (KEY_CD);
	else if (ft_strncmp(pc, "pwd", 3) == 0 && ft_isspace(*(pc + 3)))
		return (KEY_PWD);
	else if (is_letter(*pc))
		return (IDENT);
	return (ILLEGAL);
}

int	get_token_type(t_lexer *plexer)
{
	const char	*pc = plexer->input + plexer->cur_ptr;

	if (*pc == '(')
		return (LPAR);
	else if (*pc == ')')
		return (RPAR);
	else if (*pc == '|')
	{
		if (*(pc + 1) == '|')
			return (OPRT_OR);
		return (PIPE);
	}
	else if (*pc == '<')
	{
		if (*(pc + 1) == '<')
			return (RDICT_HEREDOC);
		return (RDICT_READ);
	}
	else if (*pc == '>')
	{
		if (*(pc + 1) == '>')
			return (RDICT_APPEND);
		return (RDICT_WRITE);
	}
	return (get_token_type2(plexer, pc));
}
