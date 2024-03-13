/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:33:36 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/06 23:59:22 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	buf = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, (char *) s1, (s1_len + 1));
	ft_strlcat(buf, (char *) s2, (s1_len + s2_len + 1));
	return (buf);
}
