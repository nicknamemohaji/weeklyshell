/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 04:03:00 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/10 17:33:21 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		**ft_split(char const *s, char c);
static int	ft_split_count(char const *s, char c);
static char	*ft_split_substr(const char *s, char c);
static void	*ft_split_free(char **buf);

char	**ft_split(char const *s, char c)
{
	int		flag_sep;
	char	**buf;
	char	**ptr;

	buf = malloc((ft_split_count(s, c) + 1) * sizeof(char *));
	if (buf == NULL)
		return (NULL);
	ptr = buf;
	flag_sep = 1;
	while (*s != 0)
	{
		if (*s != c && flag_sep)
		{
			*buf = ft_split_substr(s, c);
			if (*buf == NULL)
				return (ft_split_free(ptr));
			flag_sep = 0;
			buf++;
		}
		else if (*s == c)
			flag_sep = 1;
		s++;
	}
	*buf = 0;
	return (ptr);
}

static void	*ft_split_free(char **buf)
{
	char	*temp;
	char	**ptr;

	ptr = buf;
	while (*buf != NULL)
	{
		temp = *buf;
		buf++;
		free(temp);
	}
	free(ptr);
	return (NULL);
}

static char	*ft_split_substr(const char *s, char c)
{
	char	*end_pos;

	end_pos = ft_strchr(s, c);
	if (end_pos == NULL)
		end_pos = (char *)s + ft_strlen(s);
	return (ft_substr(s, 0, (end_pos - s)));
}

static int	ft_split_count(char const *s, char c)
{
	int	cnt;
	int	flag_sep;

	cnt = 0;
	flag_sep = 1;
	while (*s != 0)
	{
		if (*s != c && flag_sep)
		{
			cnt++;
			flag_sep = 0;
		}
		else if (*s == c)
			flag_sep = 1;
		s++;
	}
	return (cnt);
}
