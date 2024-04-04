/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:46:19 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 16:30:58 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			s1_size;
	size_t			s2_size;
	size_t			cmp_end;
	size_t			idx;

	s1_size = ft_strlen(s1) + 1;
	s2_size = ft_strlen(s2) + 1;
	cmp_end = (s1_size < s2_size) * s1_size + (s1_size >= s2_size) * s2_size;
	cmp_end = (n < cmp_end) * n + (n >= cmp_end) * cmp_end;
	idx = 0;
	while (idx < cmp_end)
	{
		if (s1[idx] != s2[idx])
		{
			return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
		}
		idx++;
	}
	return (0);
}
