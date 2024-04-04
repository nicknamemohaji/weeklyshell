/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_generate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:27:58 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_member.h"

t_ft_string	*ft_str_substr(t_ft_string *this, size_t start, size_t size)
{
	t_ft_string		*new_string;
	char			*tmp_buffer;
	size_t			idx;

	new_string = (t_ft_string *)malloc(sizeof(t_ft_string));
	tmp_buffer = (char *)malloc(this->capacity);
	if (new_string == NULL || tmp_buffer == NULL)
	{
		free(new_string);
		free(tmp_buffer);
		return (NULL);
	}
	new_string->pbuffer = tmp_buffer;
	new_string->capacity = this->capacity;
	new_string->size = size;
	set_string_member_function(new_string);
	idx = -1;
	while (++idx < new_string->size)
		new_string->pbuffer[idx] = this->pbuffer[start + idx];
	return (new_string);
}

t_ft_string	*ft_str_join(t_ft_string *this, t_ft_string *ftstr)
{
	t_ft_string		*new_string;

	new_string = ft_str_substr(this, 0, this->size);
	if (new_string == NULL || !ft_str_add(new_string, ftstr))
		return (NULL);
	return (new_string);
}
