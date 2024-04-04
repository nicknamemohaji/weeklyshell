/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:50:57 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 14:04:12 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**new_cmd_list(int num_cmd)
{
	char	**self;

	self = malloc(sizeof(char *) * (num_cmd + 1));
	self[num_cmd] = NULL;
	return (self);
}

void	delete_cmd_list(char **self)
{
	int	idx;

	idx = -1;
	while (self[++idx] != NULL)
		free(self[idx]);
	free(self);
}
