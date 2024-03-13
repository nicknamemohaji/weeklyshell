/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 05:54:59 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/05 06:10:01 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		idx;
	int		s_len;
	char	*buf;

	s_len = ft_strlen(s);
	buf = malloc((s_len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	idx = 0;
	while (idx < s_len)
	{
		buf[idx] = f(idx, s[idx]);
		idx++;
	}
	buf[idx] = 0;
	return (buf);
}
