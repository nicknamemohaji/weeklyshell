/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:07:24 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/09 21:07:50 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			idx;
	size_t			s_size;
	char			*result;

	idx = 0;
	s_size = ft_strlen(s) + 1;
	result = NULL;
	while (idx < s_size)
	{
		if (s[idx] == (char)c)
		{
			result = (char *)(s + idx);
			break ;
		}
		idx++;
	}
	return (result);
}
