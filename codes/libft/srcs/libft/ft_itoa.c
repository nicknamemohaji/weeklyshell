/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 04:09:55 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/07 03:07:34 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static void	ft_itoa_recursive(long n, char *buf);
static int	ft_itoa_getlen(long n);

char	*ft_itoa(int n)
{
	char	*buf;
	int		len;

	len = ft_itoa_getlen(n);
	buf = malloc((len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, (len + 1));
	if (n < 0)
	{
		buf[0] = '-';
		ft_itoa_recursive((long)n * -1, buf);
	}
	else
		ft_itoa_recursive(n, buf);
	return (buf);
}

static void	ft_itoa_recursive(long n, char *buf)
{
	int	mod;

	mod = n % 10;
	if (n >= 10)
	{
		ft_itoa_recursive(n / 10, buf);
		while (*buf != 0)
			buf++;
		*buf = mod + '0';
	}
	else
	{
		while (*buf != 0)
			buf++;
		*buf = mod + '0';
		buf++;
		*buf = 0;
	}
}

static int	ft_itoa_getlen(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	else if (n == 0)
	{
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}
