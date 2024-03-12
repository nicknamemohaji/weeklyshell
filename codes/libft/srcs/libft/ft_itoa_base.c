/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:46:52 by kyungjle          #+#    #+#             */
/*   Updated: 2024/02/16 18:44:24 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(long n, const char *base);
static void	ft_i_b_r(unsigned long n, int blen, const char *base, char *buf);
static int	ft_itoa_base_getlen(long n, int base_len);

char	*ft_itoa_base(long n, const char *base)
{
	char	*buf;
	int		len;
	int		base_len;

	base_len = ft_strlen(base);
	len = ft_itoa_base_getlen(n, base_len);
	buf = ft_calloc(len + 1, sizeof(char));
	if (buf == NULL)
		return (NULL);
	if (n < 0)
	{
		buf[0] = '-';
		ft_i_b_r(n * -1, base_len, base, buf);
	}
	else
		ft_i_b_r(n, base_len, base, buf);
	return (buf);
}

static void	ft_i_b_r(unsigned long n, int blen, const char *base, char *buf)
{
	long	mod;

	mod = (unsigned long)(n % (long) blen);
	if (n >= (unsigned int) blen)
	{
		ft_i_b_r(n / (long) blen, blen, base, buf);
		while (*buf != 0)
			buf++;
		*buf = base[mod];
	}
	else
	{
		while (*buf != 0)
			buf++;
		*buf = base[mod];
		buf++;
		*buf = 0;
	}
}

static int	ft_itoa_base_getlen(long n, int base_len)
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
		n /= base_len;
	}
	return (len);
}
