/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:53:33 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/13 21:10:22 by nicknamemoh      ###   ########.fr       */
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
	free(*ptr);
	free(ptr_ptr);
}
