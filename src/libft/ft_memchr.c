/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:13:23 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/09 18:47:34 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				idx;

	idx = -1;
	while (++idx < n)
	{
		if (((unsigned char *)s)[idx] == (unsigned char)c)
		{
			return ((void *)(idx + (unsigned char *)s));
		}
	}
	return (NULL);
}
