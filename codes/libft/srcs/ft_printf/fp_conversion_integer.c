/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_conversion_integer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:10:35 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/18 00:13:58 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fp_integer_base10_signed(long n);
char	*fp_integer_base10_unsigned(unsigned long n);
char	*fp_integer_base16(unsigned long n, int is_upper);

char	*fp_integer_base10_signed(long n)
{
	return (ft_itoa(n));
}

char	*fp_integer_base10_unsigned(unsigned long n)
{
	return (ft_itoa_base(n, "0123456789"));
}

char	*fp_integer_base16(unsigned long n, int is_upper)
{
	if (is_upper)
		return (ft_itoa_base(n, "0123456789ABCDEF"));
	else
		return (ft_itoa_base(n, "0123456789abcdef"));
}
