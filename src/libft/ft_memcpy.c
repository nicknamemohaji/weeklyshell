/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:22:39 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 11:30:27 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				idx;

	idx = -1;
	if (n == 0 || dst == src)
		return (dst);
	while (++idx < n)
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
	return (dst);
}
