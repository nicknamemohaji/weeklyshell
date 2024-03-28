/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precedence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:20:46 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:20:49 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_precedence(int token_type)
{
	if ((token_type == OPRT_AND) || (token_type == OPRT_OR))
		return (P_LOGIC);
	else if ((token_type == RDICT_READ) || (token_type == RDICT_WRITE)
		|| (token_type == RDICT_APPEND) || (token_type == RDICT_HEREDOC))
		return (P_RDICT);
	else if (token_type == PIPE)
		return (P_PIPE);
	else
		return (P_NO_MATCH);
}
