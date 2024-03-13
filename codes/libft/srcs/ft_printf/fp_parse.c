/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:11:53 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 03:11:28 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fp_parse_format(const char **s, va_list va, char *conv);
char	*fp_parse_normal(const char **s);

char	*fp_parse_normal(const char **s)
{
	char	*ret;
	char	*pos;
	size_t	len;

	pos = ft_strchr((*s + 1), '%');
	if (pos == NULL)
		len = ft_strlen(*s);
	else
		len = pos - *s;
	ret = ft_substr(*s, 0, len);
	if (ret == NULL)
		return (NULL);
	*s += ft_strlen(ret);
	return (ret);
}

char	*fp_parse_format(const char **s, va_list va, char *conv)
{
	char	c;
	int		flag;
	int		width;
	char	conversion;

	*s = *s + 1;
	while (1)
	{
		c = **s;
		*s = *s + 1;
		if (c == 'c' || c == 's' || c == 'p' || c == 'i' || c == '%'
			|| c == 'u' || c == 'x' || c == 'X' || c == 'd')
		{
			conversion = c;
			break ;
		}
	}
	flag = -1;
	width = -1;
	*conv = conversion;
	return (fp_conversion(flag, width, conversion, va));
}
