/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:48:08 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/07 03:07:16 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (*s2 == 0)
		return ((char *)s1);
	while (n > 0 && *s1 != 0)
	{
		if (*s1 == *s2)
		{
			i = 0;
			while (s1[i] != 0 && s2[i] != 0)
			{
				if (s1[i] != s2[i])
					break ;
				i++;
			}
			if (s2[i] == 0 && n >= i)
				return ((char *)s1);
		}
		n--;
		s1++;
	}
	return (0);
}
