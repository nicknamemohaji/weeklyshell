/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:47 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/18 19:23:29 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest <= src && src <= (dest + n) && n != 0)
	{
		i = 0;
		while (i < n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	else if (n != 0)
	{
		i = n - 1;
		while (i > 0)
		{
			((char *) dest)[i] = ((char *) src)[i];
			if (i == 0)
				break ;
			i--;
		}
		((char *) dest)[i] = ((char *) src)[i];
	}
	return (dest);
}
