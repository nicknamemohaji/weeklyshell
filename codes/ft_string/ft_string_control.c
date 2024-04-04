/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:03:59 by dogwak            #+#    #+#             */
/*   Updated: 2023/11/23 12:42:13 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_member.h"

// clear does not means deleting pbuffer
void	ft_str_clear(t_ft_string *this)
{
	this->size = 0;
}

// resize the string's capacity and copy the content.
// resizing string to 0 is forbidden
// after resizing, the content can be truncated.
int	ft_str_resize(t_ft_string *this, size_t size)
{
	char	*tmp_buffer;
	size_t	idx;
	size_t	iter;

	if (size == 0)
		return (0);
	tmp_buffer = (char *)malloc(sizeof(char) * size);
	if (tmp_buffer == NULL)
		return (0);
	this->capacity = size;
	if (this->size != 0)
	{
		idx = -1;
		iter = (this->size < size) * this->size + (this->size >= size) * size;
		while (++idx < iter)
			tmp_buffer[idx] = this->pbuffer[idx];
		this->size = idx;
	}
	free(this->pbuffer);
	this->pbuffer = tmp_buffer;
	return (1);
}

int	ft_str_push_back(t_ft_string *this, char c)
{
	if (this->size == this->capacity)
		if (!ft_str_resize(this, this->capacity * 2))
			return (0);
	this->pbuffer[this->size++] = c;
	return (1);
}

int	ft_str_append(t_ft_string *this, char *cstr)
{
	size_t			idx;

	idx = -1;
	while (cstr[++idx] != '\0')
		if (!ft_str_push_back(this, cstr[idx]))
			return (0);
	return (1);
}

int	ft_str_add(t_ft_string *this, t_ft_string *ftstr)
{
	size_t			idx;

	idx = -1;
	while (++idx < ftstr->size)
		if (!ft_str_push_back(this, ftstr->pbuffer[idx]))
			return (0);
	return (1);
}
