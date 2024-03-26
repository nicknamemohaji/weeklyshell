/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:40:49 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/23 20:59:07 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	max_pow_10(long long num)
{
	long long				result;

	result = 1;
	while ((num / result) >= 10)
		result *= 10;
	return (result);
}

// str's size has to be 12
// 10 for num, 1 for sign, 1 for NULL
void	ft_conv_itoa(char *str, long long num)
{
	size_t				idx;
	long long			divider;

	idx = 0;
	if (num < 0)
	{
		num *= -1;
		str[idx++] = '-';
	}
	divider = max_pow_10(num);
	while (divider > 0)
	{
		str[idx++] = (num / divider) + '0';
		num %= divider;
		divider /= 10;
	}
	str[idx] = '\0';
}
