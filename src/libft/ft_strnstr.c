/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:38:51 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 12:26:20 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hay_len;
	size_t	needle_len;
	size_t	end;
	size_t	hay_idx;
	size_t	needle_idx;

	hay_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	end = (len < hay_len) * len + (len >= hay_len) * hay_len;
	hay_idx = -1;
	while (++hay_idx + needle_len < end + 1)
	{
		needle_idx = -1;
		while (++needle_idx < needle_len)
		{
			if (needle[needle_idx] != haystack[hay_idx + needle_idx])
				break ;
		}
		if (needle_idx == needle_len)
			return ((char *)(haystack + hay_idx));
	}
	return (NULL);
}
