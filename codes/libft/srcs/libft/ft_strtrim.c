/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:38:52 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/10 17:03:47 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		end;
	char		*buf;

	while (*s1 != 0)
	{
		if (ft_strchr(set, *s1) == NULL)
			break ;
		s1++;
	}
	if (ft_strlen(s1) == 0)
	{
		buf = malloc(1);
		if (buf == NULL)
			return (NULL);
		*buf = 0;
		return (buf);
	}
	end = (ft_strlen(s1) - 1);
	while (end > 0)
	{
		if (ft_strchr(set, s1[end]) == NULL)
			break ;
		end--;
	}
	return (ft_substr(s1, 0, (end + 1)));
}
