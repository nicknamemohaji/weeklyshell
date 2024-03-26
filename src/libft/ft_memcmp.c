/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:05:42 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/09 18:48:21 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				idx;

	idx = -1;
	while (++idx < n)
	{
		if (((unsigned char *)s1)[idx] != ((unsigned char *)s2)[idx])
		{
			return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
		}
	}
	return (0);
}
