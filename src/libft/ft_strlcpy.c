/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:46:56 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 16:29:56 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			src_len;
	size_t			idx;

	src_len = ft_strlen(src);
	idx = 0;
	while (idx < src_len && (idx + 1) < dstsize)
	{
		dst[idx] = src[idx];
		idx++;
	}
	if (dstsize > 0)
		dst[idx] = '\0';
	return (src_len);
}
