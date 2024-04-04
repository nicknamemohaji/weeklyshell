/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:11 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/21 11:49:28 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_bool	input_validate(const char *input);

/*
t_bool	input_validate(const char *input)
:param input: user input to check
:return: TRUE if the input is valid, FALSE otherwise

Checks for unclosed quotes or unclosed parenthesis
- quotes/parenthesis inside other types are considered
*/
t_bool	input_validate(const char *input)
{
	t_bool	squote_closed;
	t_bool	dquote_closed;
	t_bool	paren_closed;

	squote_closed = TRUE;
	dquote_closed = TRUE;
	paren_closed = TRUE;
	while (*input != '\0')
	{
		if (*input == '\'' && dquote_closed)
			squote_closed = !squote_closed;
		else if (*input == '\"' && squote_closed)
			dquote_closed = !dquote_closed;
		else if (*input == '(' && dquote_closed && squote_closed)
			paren_closed = FALSE;
		else if (*input == ')' && dquote_closed && squote_closed)
			paren_closed = !paren_closed;
		input++;
	}
	return (squote_closed & dquote_closed & paren_closed);
}
