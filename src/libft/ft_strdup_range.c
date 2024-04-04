/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:43 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 16:42:24 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_range(const char *origin, size_t start, size_t end)
{
	char			*dst;
	size_t			idx;

	if (start > end)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (end - start + 1));
	if (dst == NULL)
		return (NULL);
	idx = 0;
	while (idx + start < end)
	{
		dst[idx] = origin[start + idx];
		idx++;
	}
	dst[idx] = '\0';
	return (dst);
}
