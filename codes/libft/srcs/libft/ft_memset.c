/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:09:35 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/10 15:28:34 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n);

void	*ft_memset(void *s, int c, size_t n)
{
	void	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		*(char *)s = (unsigned char) c;
		s++;
		i++;
	}
	return (ptr);
}
