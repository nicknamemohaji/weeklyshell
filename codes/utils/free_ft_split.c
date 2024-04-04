/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:53:33 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/04 15:44:11 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_ft_split(char **ptr);

/*
void	free_ft_split(char **ptr)
:param ptr: result of ft_split function to be freed
*/
void	free_ft_split(char **ptr)
{
	char	**ptr_ptr;

	ptr_ptr = ptr;
	while (*ptr != NULL)
		free(*(ptr++));
	free(ptr_ptr);
}
