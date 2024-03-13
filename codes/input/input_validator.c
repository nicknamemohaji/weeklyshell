/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:19:11 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/12 22:19:17 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_bool	input_validate(const char *input);

t_bool	input_validate(const char *input)
{
	t_bool	squote_closed;
	t_bool	dquote_closed;

	squote_closed = TRUE;
	dquote_closed = TRUE;
	while (*input != '\0')
	{
		if (*input == '\'' && dquote_closed)
			squote_closed = !squote_closed;
		else if (*input == '\"' && squote_closed)
			dquote_closed = !dquote_closed;
		input++;
	}
	return (squote_closed & dquote_closed);
}
