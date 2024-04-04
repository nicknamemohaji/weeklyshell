/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:41:56 by dogwak            #+#    #+#             */
/*   Updated: 2024/01/01 11:39:39 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_member.h"

void	delete_ftvec(t_ft_vector *this)
{
	size_t	idx;

	idx = -1;
	if (this->pbuffer != NULL)
	{
		while (++idx < this->size)
			this->delete_data(this->pbuffer + idx * this->data_size);
		free(this->pbuffer);
	}
	free(this);
}

t_ft_vector	*new_ftvec(int (*cd)(void *paddr, void *pparam),
		void (*dd)(void *paddr), size_t s)
{
	t_ft_vector	*this;
	void		*tmp_buffer;

	this = (t_ft_vector *)malloc(sizeof(t_ft_vector));
	tmp_buffer = malloc(s * DEFAULT_FT_VECTOR_SIZE);
	if (this == NULL || tmp_buffer == NULL)
	{
		free(this);
		free(tmp_buffer);
		return (NULL);
	}
	this->pbuffer = tmp_buffer;
	this->construct_data = cd;
	this->delete_data = dd;
	this->capacity = DEFAULT_FT_VECTOR_SIZE;
	this->size = 0;
	this->data_size = s;
	set_vector_member_function(this);
	return (this);
}

t_ft_vector	*new_ftvec_copy(t_ft_vector *src, int (*copy)(void *pdst_data,
			void *psrc_data))
{
	t_ft_vector	*this;

	this = new_ftvec(src->construct_data, src->delete_data, src->data_size);
	if (this == NULL)
		return (NULL);
	if (!this->resize(this, src->capacity))
	{
		delete_ftvec(this);
		return (NULL);
	}
	this->size = 0;
	while (this->size < src->size)
	{
		if (copy(this->at(this, this->size), src->at(src, this->size)))
		{
			this->size++;
			delete_ftvec(this);
			return (NULL);
		}
		this->size++;
	}
	return (this);
}
