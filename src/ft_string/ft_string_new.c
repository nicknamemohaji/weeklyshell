/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:43:19 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_member.h"

t_ft_string	*new_ftstr(void)
{
	t_ft_string		*this;
	char			*tmp_buffer;

	this = (t_ft_string *)malloc(sizeof(t_ft_string));
	tmp_buffer = (char *)malloc(DEFAULT_FT_STRING_SIZE);
	if (this == NULL || tmp_buffer == NULL)
	{
		free(this);
		free(tmp_buffer);
		return (NULL);
	}
	this->pbuffer = tmp_buffer;
	this->capacity = DEFAULT_FT_STRING_SIZE;
	this->size = 0;
	set_string_member_function(this);
	return (this);
}

t_ft_string	*new_ftstr_len(size_t len)
{
	t_ft_string		*this;
	char			*tmp_buffer;

	if (len == 0)
		len = DEFAULT_FT_STRING_SIZE;
	this = (t_ft_string *)malloc(sizeof(t_ft_string));
	tmp_buffer = (char *)malloc(len);
	if (this == NULL || tmp_buffer == NULL)
	{
		free(this);
		free(tmp_buffer);
		return (NULL);
	}
	this->pbuffer = tmp_buffer;
	this->capacity = len;
	this->size = 0;
	set_string_member_function(this);
	return (this);
}

t_ft_string	*new_ftstr_cstr(char *cstr)
{
	t_ft_string		*this;
	size_t			idx;

	this = new_ftstr();
	if (this == NULL)
		return (NULL);
	idx = -1;
	while (cstr[++idx] != '\0')
	{
		if (idx == this->capacity)
		{
			if (!ft_str_resize(this, 2 * this->capacity))
			{
				free(this->pbuffer);
				free(this);
				return (NULL);
			}
		}
		this->pbuffer[idx] = cstr[idx];
		this->size++;
	}
	return (this);
}

t_ft_string	*new_ftstr_copy(t_ft_string *ftstr)
{
	t_ft_string		*new_string;
	char			*tmp_buffer;
	size_t			idx;

	new_string = (t_ft_string *)malloc(sizeof(t_ft_string));
	tmp_buffer = (char *)malloc(ftstr->capacity);
	if (new_string == NULL || tmp_buffer == NULL)
	{
		free(new_string);
		free(tmp_buffer);
		return (NULL);
	}
	*new_string = *ftstr;
	new_string->pbuffer = tmp_buffer;
	idx = -1;
	while (++idx < new_string->size)
		new_string->pbuffer[idx] = ftstr->pbuffer[idx];
	return (new_string);
}

void	delete_ftstr(t_ft_string *ftstr)
{
	if (ftstr != NULL)
		free(ftstr->pbuffer);
	free(ftstr);
}
