/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:09:18 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/13 17:17:16 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char delim)
{
	size_t			idx;
	int				cnt;
	int				delim_flag;

	idx = 0;
	cnt = 0;
	delim_flag = 1;
	while (str[idx] != '\0')
	{
		if (str[idx] != delim && delim_flag == 1)
		{
			cnt++;
			delim_flag = 0;
		}
		else if (str[idx] == delim && delim_flag == 0)
		{
			delim_flag = 1;
		}
		idx++;
	}
	return (cnt);
}

static char	**free_all(char **str_arr)
{
	size_t			idx;

	idx = -1;
	while (str_arr[++idx] != NULL)
	{
		free(str_arr[idx]);
		str_arr[idx] = NULL;
	}
	free(str_arr);
	str_arr = NULL;
	return (NULL);
}

static	char	**set_var(int num_word, size_t *pidx,
	size_t *pstr_idx, int *pflag)
{
	*pidx = -1;
	*pstr_idx = 0;
	*pflag = 1;
	return ((char **)malloc(sizeof(char *) * (num_word + 1)));
}

char	**ft_split(char const *s, char c)
{
	char				**str_arr;
	size_t				idx;
	size_t				str_idx;
	int					delim_flag;
	int					range_start;

	str_arr = set_var(count_words(s, c), &idx, &str_idx, &delim_flag);
	if (str_arr == NULL)
		return (NULL);
	while (++idx <= ft_strlen(s))
	{
		if ((s[idx] != c && s[idx] != '\0') && delim_flag == 1)
			range_start = idx;
		if ((s[idx] != c && s[idx] != '\0') && delim_flag == 1)
			delim_flag = 0;
		else if ((s[idx] == c || s[idx] == '\0') && delim_flag == 0)
		{
			str_arr[str_idx] = ft_strdup_range(s, range_start, idx);
			if (str_arr[str_idx++] == NULL)
				return (free_all(str_arr));
			delim_flag = 1;
		}
	}
	str_arr[str_idx] = NULL;
	return (str_arr);
}
