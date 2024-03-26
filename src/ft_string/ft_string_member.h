/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_member.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:45:56 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 13:01:40 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_MEMBER_H
# define FT_STRING_MEMBER_H

# include "ft_string_struct.h"

# ifndef DEFAULT_FT_STRING_SIZE
#  define DEFAULT_FT_STRING_SIZE 256
# endif

// ft_string_set_member_function
void		set_string_member_function(t_ft_string *this);

// string access functions
char		*ft_str_at(t_ft_string *this, size_t idx);
char		*ft_str_front(t_ft_string *this);
char		*ft_str_back(t_ft_string *this);
int			ft_str_empty(t_ft_string *this);

// string control functions
void		ft_str_clear(t_ft_string *this);
int			ft_str_push_back(t_ft_string *this, char c);
int			ft_str_resize(t_ft_string *this, size_t size);
int			ft_str_append(t_ft_string *this, char *cstr);
int			ft_str_add(t_ft_string *this, t_ft_string *ftstr);

// string generate functions
t_ft_string	*ft_str_join(t_ft_string *this, t_ft_string *ftstr);
t_ft_string	*ft_str_substr(t_ft_string *this, size_t start, size_t size);

// utility functions
int			ft_str_compare(t_ft_string *this, t_ft_string *ftstr);
char		*ft_str_c_str(t_ft_string *this);
int			ft_str_getline(t_ft_string *this, int fd);
int			ft_str_getword(t_ft_string *this, int fd);

#endif
