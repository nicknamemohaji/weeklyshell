/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:13:53 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/13 17:17:44 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t				alloc_size;
	unsigned char		*palloc;
	size_t				idx;

	alloc_size = count * size;
	palloc = (unsigned char *)malloc(alloc_size);
	if (palloc == NULL)
		return (NULL);
	idx = 0;
	while (idx < alloc_size)
	{
		palloc[idx] = 0;
		idx++;
	}
	return ((void *)palloc);
}
