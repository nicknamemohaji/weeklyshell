/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:27:13 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/06 20:35:45 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	char	*last_ptr;

	c = (unsigned char) c;
	last_ptr = 0;
	while (*s != 0)
	{
		if ((unsigned char)(*s) == c)
			last_ptr = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	else
		return (last_ptr);
}
