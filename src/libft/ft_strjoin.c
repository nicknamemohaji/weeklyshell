/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:09:43 by dogwak            #+#    #+#             */
/*   Updated: 2023/10/12 18:59:38 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t				dst_size;
	char				*str;

	dst_size = ft_strlen(s1);
	dst_size += ft_strlen(s2) + 1;
	str = (char *)malloc((dst_size) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, dst_size);
	ft_strlcat(str, s2, dst_size);
	return (str);
}
