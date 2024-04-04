/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_member.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:18:27 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:44:52 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_MEMBER_H
# define FT_VECTOR_MEMBER_H

# include "ft_vector_struct.h"

# ifndef DEFAULT_FT_VECTOR_SIZE
#  define DEFAULT_FT_VECTOR_SIZE 256
# endif

// set member function
void		set_vector_member_function(t_ft_vector *this);

// vector contents access functions
void		*ft_vec_at(t_ft_vector *this, size_t idx);
void		*ft_vec_front(t_ft_vector *this);
void		*ft_vec_back(t_ft_vector *this);
int			ft_vec_empty(t_ft_vector *this);

// vector control functions
void		ft_vec_clear(t_ft_vector *this);
int			ft_vec_push_back(t_ft_vector *this, void *param);
int			ft_vec_resize(t_ft_vector *this, size_t new_size);

#endif
