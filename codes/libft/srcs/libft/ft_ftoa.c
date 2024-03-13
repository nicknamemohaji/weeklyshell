/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:06:19 by kyungjle          #+#    #+#             */
/*   Updated: 2024/01/03 20:07:36 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ftoa(float n);
static int	ft_ftoa_getfloating(float n);

char	*ft_ftoa(float n)
{
	char	*buf;
	char	*n_integer;
	char	*n_float;

	n_integer = ft_itoa((int) n);
	if (n_integer == NULL)
		return (NULL);
	n_float = ft_itoa(ft_ftoa_getfloating(n));
	if (n_float == NULL)
	{
		free(n_integer);
		return (NULL);
	}
	buf = ft_calloc(ft_strlen(n_integer) + ft_strlen(n_float) + 2, 1);
	if (buf != NULL)
	{
		ft_strlcat(buf, n_integer, ft_strlen(n_integer) + 1);
		ft_strlcat(buf, ".", ft_strlen(buf) + 2);
		ft_strlcat(buf, n_float, ft_strlen(buf) + ft_strlen(n_float) + 1);
	}
	free(n_integer);
	free(n_float);
	return (buf);
}

static int	ft_ftoa_getfloating(float n)
{
	float	n_float;
	int		len;

	len = 0;
	if (n < 0)
		n *= -1;
	n_float = n - (int)n;
	if (n_float == 0.0)
		return (0);
	while (n_float - (int)n_float != 0)
	{
		len++;
		n_float *= 10;
		n_float = n_float - (int)n_float;
	}
	while (len > 0)
	{
		len--;
		n *= 10;
	}
	return ((int) n);
}
