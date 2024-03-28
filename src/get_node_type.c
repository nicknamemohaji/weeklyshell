/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:21:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:21:20 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_prefix_node_type(int token_type)
{
	if (token_type == RDICT_WRITE)
		return (EXP_PRE_RWRITE);
	else if (token_type == RDICT_APPEND)
		return (EXP_PRE_RAPPEND);
	else if (token_type == RDICT_READ)
		return (EXP_PRE_RREAD);
	else if (token_type == RDICT_HEREDOC)
		return (EXP_PRE_RHEREDOC);
	else if (KEY_ECHO <= token_type && token_type <= IDENT)
		return (NODE_WORD);
	else
		return (NODE_ERROR);
}

int	get_infix_node_type(int token_type)
{
	if (token_type == PIPE)
		return (EXP_IN_PIPE);
	else if (token_type == OPRT_AND)
		return (EXP_IN_AND);
	else if (token_type == OPRT_OR)
		return (EXP_IN_OR);
	else if (token_type == RDICT_WRITE)
		return (EXP_IN_RWRITE);
	else if (token_type == RDICT_APPEND)
		return (EXP_IN_RAPPEND);
	else
		return (NODE_ERROR);
}
