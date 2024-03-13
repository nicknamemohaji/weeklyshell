/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:01:05 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/17 17:54:44 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str);

int	ft_atoi(const char *str)
{
	long	sign;
	long	acc;

	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	acc = 0;
	while ('0' <= *str && *str <= '9')
	{
		acc = (acc * 10) + (*str - '0');
		str++;
	}
	return ((int)(acc * sign));
}
