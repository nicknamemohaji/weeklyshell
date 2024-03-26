/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:53:59 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 11:30:11 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				idx;

	if (len == 0 || dst == src)
		return (dst);
	if (dst <= src)
	{
		idx = 0;
		while (idx < len)
		{
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
			idx++;
		}
	}
	else
	{
		idx = len - 1;
		while (1)
		{
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
			if (idx == 0)
				break ;
			idx--;
		}
	}
	return (dst);
}
