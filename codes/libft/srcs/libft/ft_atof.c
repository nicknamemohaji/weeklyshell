/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 00:13:20 by kyungjle          #+#    #+#             */
/*   Updated: 2023/12/29 03:40:35 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_atof(const char *str);
static int	ft_atof_sign(const char **str);

float	ft_atof(const char *str)
{
	int		sign;
	int		integer_value;
	float	floating_value;
	int		float_length;

	integer_value = 0;
	floating_value = 0;
	float_length = 0;
	sign = ft_atof_sign(&str);
	while (*str != '.')
	{
		integer_value = integer_value * 10 + (*str - '0');
		str++;
	}
	str++;
	while (*str != '\0')
	{
		floating_value = floating_value * 10 + (*str - '0');
		float_length++;
		str++;
	}
	while (float_length-- > 0)
		floating_value *= 0.1f;
	return ((float) sign * ((float) integer_value + floating_value));
}

static int	ft_atof_sign(const char **str)
{
	if (**str == '-')
	{
		*str += 1;
		return (-1);
	}
	else if (**str == '+')
		*str += 1;
	return (1);
}
