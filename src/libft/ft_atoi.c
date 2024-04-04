/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:31:34 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 16:15:27 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	conv_num(const char *str)
{
	size_t			idx;
	long long		num;

	idx = 0;
	num = 0;
	while (str[idx] != '\0' && ft_isdigit(str[idx]))
	{
		num *= 10;
		num += str[idx] - '0';
		idx++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	size_t			idx;
	long long		num;
	int				is_minus;

	idx = 0;
	is_minus = 0;
	while (ft_isspace(str[idx]))
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx] == '-')
			is_minus = 1;
		idx++;
	}
	num = conv_num(str + idx);
	if (is_minus)
		num *= -1;
	return ((int)num);
}
