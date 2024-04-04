/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:12:02 by dogwak            #+#    #+#             */
/*   Updated: 2024/01/01 11:39:27 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * C++ like, norminette compatible vector container
 * do not use this code with C++ runtime

	made by dogwak
*/

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "ft_vector_struct.h"

/*
class t_ft_vector
{
	void			*at(struct s_ft_vec *this, size_t idx);
	void			*front(struct s_ft_vec *this);
	void			*back(struct s_ft_vec *this);
	int				empty(struct s_ft_vec *this);
	void			clear(struct s_ft_vec *this);
	int				push_back(struct s_ft_vec *this, void *elem);
	int				resize(struct s_ft_vec *this, size_t size);
}
*/

// default constructor
t_ft_vector	construct_ftvec(int (*cd)(void *paddr, void *pparam),
				void (*dd)(void *paddr), size_t s);

// copy constructor
t_ft_vector	construct_ftvec_copy(t_ft_vector *src, int (*copy)(void *pdst_data,
					void *psrc_data));

// destructor
void		destruct_ftvec(t_ft_vector *this);

t_ft_vector	*new_ftvec(int (*cd)(void *paddr, void *pparam),
				void (*dd)(void *paddr), size_t s);

t_ft_vector	*new_ftvec_copy(t_ft_vector *src, int (*copy)(void *pdst_data,
					void *psrc_data));

void		delete_ftvec(t_ft_vector *this);

#endif
