/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_conversion_wrapper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:13:09 by kyungjle          #+#    #+#             */
/*   Updated: 2024/03/18 19:23:10 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fp_valid_conversion(char *s);
char	*fp_conversion(int flag, int width, char conversion, va_list va);

int	fp_valid_conversion(char *s)
{
	s++;
	while ((*s == '#' || *s == ' ' || *s == '+'
			|| *s == '-' || *s == '0' || *s == '.') && *s != 0)
		s++;
	if (*s == 0)
		return (0);
	if ('0' <= *s && *s <= '9')
		while (('0' <= *s && *s <= '9') && *s != 0)
			s++;
	else if (*s == '*')
	{
		s++;
		while (('0' <= *s && *s <= '9') && *s != 0)
			s++;
		if (*s != '$')
			return (0);
		s++;
	}
	if ((*s == 'c' || *s == 's' || *s == 'p' || *s == 'i' || *s == '%'
			|| *s == 'u' || *s == 'x' || *s == 'X' || *s == 'd') && *s != 0)
		return (1);
	else
		return (0);
}

char	*fp_conversion(int flag, int width, char conversion, va_list va)
{
	flag++;
	width++;
	if (conversion == 'd' || conversion == 'i')
		return (fp_integer_base10_signed(va_arg(va, int)));
	if (conversion == 'u')
		return (fp_integer_base10_unsigned(va_arg(va, unsigned int)));
	else if (conversion == 'x')
		return (fp_integer_base16(va_arg(va, unsigned int), 0));
	else if (conversion == 'X')
		return (fp_integer_base16(va_arg(va, unsigned int), 1));
	else if (conversion == 'c')
		return (fp_char(va_arg(va, int)));
	else if (conversion == 's')
		return (fp_string(va_arg(va, char *)));
	else if (conversion == 'p')
		return (fp_ptr(va_arg(va, void *)));
	else if (conversion == '%')
		return (fp_percent());
	else
		return (NULL);
}
