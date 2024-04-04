/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:57:47 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/10 16:51:42 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_map(int *map, char const *str)
{
	size_t			idx;

	idx = -1;
	while (++idx < 256)
		map[idx] = 0;
	idx = -1;
	while (str[++idx])
		map[(int)(str[idx])] = 1;
}

static size_t	left_trim_pos(char const *str, int *char_map)
{
	size_t				idx;
	int					flag;
	size_t				start;

	idx = -1;
	flag = 1;
	start = 0;
	while (str[++idx] != '\0')
	{
		if (!char_map[(int)(str[idx])] && flag == 1)
		{
			start = idx;
			flag = 0;
		}
	}
	return (start);
}

static size_t	right_trim_pos(char const *str, int *char_map)
{
	size_t				idx;
	int					flag;
	size_t				end;

	idx = ft_strlen(str) - 1;
	if (idx == (size_t)(-1))
		return (0);
	flag = 1;
	end = 0;
	while (1)
	{
		if (!char_map[(int)(str[idx])] && flag == 1)
		{
			end = idx + 1;
			flag = 0;
		}
		if (idx == 0)
			break ;
		idx--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int					char_map[256];
	size_t				start;
	size_t				end;

	set_map(char_map, set);
	start = left_trim_pos(s1, char_map);
	end = right_trim_pos(s1, char_map);
	return (ft_strdup_range(s1, start, end));
}
