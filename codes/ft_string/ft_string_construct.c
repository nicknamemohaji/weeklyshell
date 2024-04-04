/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:50:28 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_member.h"

t_ft_string	construct_ftstr(void)
{
	t_ft_string		this;
	char			*tmp_buffer;

	tmp_buffer = (char *)malloc(DEFAULT_FT_STRING_SIZE);
	this.pbuffer = tmp_buffer;
	this.capacity = DEFAULT_FT_STRING_SIZE;
	this.size = 0;
	set_string_member_function(&this);
	return (this);
}

t_ft_string	construct_ftstr_len(size_t len)
{
	t_ft_string		this;
	char			*tmp_buffer;

	if (len == 0)
		len = DEFAULT_FT_STRING_SIZE;
	tmp_buffer = (char *)malloc(len);
	this.pbuffer = tmp_buffer;
	this.capacity = len;
	this.size = 0;
	set_string_member_function(&this);
	return (this);
}

t_ft_string	construct_ftstr_cstr(char *cstr)
{
	t_ft_string		this;
	size_t			idx;

	this = construct_ftstr();
	if (this.pbuffer == NULL || cstr == NULL)
	{
		free(this.pbuffer);
		return (this);
	}
	idx = -1;
	while (cstr[++idx] != '\0')
	{
		if (idx == this.capacity)
		{
			if (!ft_str_resize(&this, 2 * this.capacity))
			{
				free(this.pbuffer);
				this.pbuffer = NULL;
				return (this);
			}
		}
		this.pbuffer[idx] = cstr[idx];
		this.size++;
	}
	return (this);
}

t_ft_string	construct_ftstr_copy(t_ft_string *ftstr)
{
	t_ft_string		new_string;
	char			*tmp_buffer;
	size_t			idx;

	tmp_buffer = (char *)malloc(ftstr->capacity);
	if (tmp_buffer == NULL || ftstr == NULL)
	{
		free(tmp_buffer);
		new_string.pbuffer = NULL;
		return (new_string);
	}
	new_string = *ftstr;
	new_string.pbuffer = tmp_buffer;
	idx = -1;
	while (++idx < new_string.size)
		new_string.pbuffer[idx] = ftstr->pbuffer[idx];
	return (new_string);
}

void	destruct_ftstr(t_ft_string *ftstr)
{
	if (ftstr != NULL)
		free(ftstr->pbuffer);
}
