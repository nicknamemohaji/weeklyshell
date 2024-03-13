/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_conversion_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:15:47 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 10:21:32 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fp_ptr(void *p);
char	*fp_percent(void);

char	*fp_ptr(void *p)
{
	char	*buf;
	char	*buf2;

	buf = fp_integer_base16((unsigned long) p, 0);
	if (buf == NULL)
		return (NULL);
	buf2 = ft_strjoin("0x", buf);
	free(buf);
	return (buf2);
}

char	*fp_percent(void)
{
	return (ft_strdup("%"));
}
