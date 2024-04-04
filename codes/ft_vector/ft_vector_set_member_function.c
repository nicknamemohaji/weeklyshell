/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set_member_function.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:42:45 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:44:33 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_member.h"

void	set_vector_member_function(t_ft_vector *this)
{
	this->at = ft_vec_at;
	this->front = ft_vec_front;
	this->back = ft_vec_back;
	this->empty = ft_vec_empty;
	this->clear = ft_vec_clear;
	this->push_back = ft_vec_push_back;
	this->resize = ft_vec_resize;
}
