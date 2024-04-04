/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:10:36 by dogwak            #+#    #+#             */
/*   Updated: 2023/11/27 19:57:35 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_member.h"

void	*ft_vec_at(t_ft_vector *this, size_t idx)
{
	if (this->size <= idx)
		return (NULL);
	return (this->pbuffer + idx * this->data_size);
}

void	*ft_vec_front(t_ft_vector *this)
{
	if (this->size == 0)
		return (NULL);
	return (this->pbuffer);
}

void	*ft_vec_back(t_ft_vector *this)
{
	if (this->size == 0)
		return (NULL);
	return (this->pbuffer + (this->size - 1) * this->data_size);
}

int	ft_vec_empty(t_ft_vector *this)
{
	return (this->size == 0);
}
