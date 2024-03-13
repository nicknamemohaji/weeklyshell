/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:27:38 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/07 03:13:38 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*src;
	char	*buf;
	size_t	buf_len;

	if (ft_strlen(s) <= (size_t) start)
	{
		buf = malloc(1);
		if (buf == NULL)
			return (NULL);
		*buf = 0;
		return (buf);
	}
	if (len > (ft_strlen(s) - (size_t) start))
		buf_len = (ft_strlen(s) - (size_t) start) + 1;
	else
		buf_len = len + 1;
	buf = malloc(buf_len * sizeof(char));
	if (buf == NULL)
		return (NULL);
	src = (char *)s + start;
	ft_strlcpy(buf, src, buf_len);
	return (buf);
}
