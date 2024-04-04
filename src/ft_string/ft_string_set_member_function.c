/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_set_member_function.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:44:07 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_member.h"

void	set_string_member_function(t_ft_string *this)
{
	this->at = ft_str_at;
	this->front = ft_str_front;
	this->back = ft_str_back;
	this->empty = ft_str_empty;
	this->compare = ft_str_compare;
	this->clear = ft_str_clear;
	this->push_back = ft_str_push_back;
	this->resize = ft_str_resize;
	this->join = ft_str_join;
	this->substr = ft_str_substr;
	this->append = ft_str_append;
	this->add = ft_str_add;
	this->c_str = ft_str_c_str;
	this->getline = ft_str_getline;
	this->getword = ft_str_getword;
}
