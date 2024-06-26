/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_heredoc_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:31:52 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/09 15:57:05 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	construct_heredoc_name(void *pos, void *param)
{
	param++;
	*((char **)pos) = ldexec_heredoc_assign_f();
	if (*((char **)pos) == NULL)
		return (0);
	return (1);
}

void	destruct_heredoc_name(void *pos)
{
	free(*(char **)pos);
}
