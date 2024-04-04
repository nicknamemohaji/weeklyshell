/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:27:44 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 14:00:14 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_member.h"

void	destruct_ftvec(t_ft_vector *this)
{
	size_t		idx;

	idx = -1;
	if (this->pbuffer != NULL)
	{
		while (++idx < this->size)
			this->delete_data(this->pbuffer + idx * this->data_size);
		free(this->pbuffer);
	}
}

t_ft_vector	construct_ftvec(
				int (*cd)(void *paddr, void *pparam),
				void (*dd)(void *paddr),
				size_t s)
{
	t_ft_vector	this;
	void		*tmp_buffer;

	tmp_buffer = malloc(s * DEFAULT_FT_VECTOR_SIZE);
	this.pbuffer = tmp_buffer;
	this.construct_data = cd;
	this.delete_data = dd;
	this.capacity = DEFAULT_FT_VECTOR_SIZE;
	this.size = 0;
	this.data_size = s;
	set_vector_member_function(&this);
	return (this);
}

t_ft_vector	construct_ftvec_copy(
				t_ft_vector *src,
				int (*copy)(void *pdst_data, void *psrc_data))
{
	t_ft_vector		this;

	this = construct_ftvec(src->construct_data, src->delete_data,
			src->data_size);
	if (this.pbuffer == NULL)
		return (this);
	if (!this.resize(&this, src->capacity))
	{
		destruct_ftvec(&this);
		this.pbuffer = NULL;
		return (this);
	}
	this.size = 0;
	while (this.size < src->size)
	{
		if (copy(this.at(&this, this.size), src->at(src, this.size)))
		{
			this.size++;
			destruct_ftvec(&this);
			this.pbuffer = NULL;
			return (this);
		}
		this.size++;
	}
	return (this);
}
