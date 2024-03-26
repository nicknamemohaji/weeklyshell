/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:56:38 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 15:53:58 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_empty_string(char **str)
{
	*str = (char *)malloc(sizeof(char));
	if (*str == NULL)
		return (NULL);
	(*str)[0] = '\0';
	return (*str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			idx;
	size_t			s_len;
	size_t			substr_s;

	s_len = ft_strlen(s);
	if (s_len <= start || len == 0)
	{
		return (set_empty_string(&str));
	}
	substr_s = s_len - start;
	substr_s = (len >= substr_s) * substr_s + (len < substr_s) * len + 1;
	str = (char *)malloc((substr_s) * sizeof(char));
	if (str == NULL)
		return (NULL);
	idx = 0;
	while (idx < len && s[start + idx] != '\0')
	{
		str[idx] = s[start + idx];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
