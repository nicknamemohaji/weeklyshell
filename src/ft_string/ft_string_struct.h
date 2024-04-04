/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:30:01 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/12 11:37:46 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_STRUCT_H
# define FT_STRING_STRUCT_H

# include <stdlib.h>

typedef struct s_ft_str
{
	char			*pbuffer;
	size_t			size;
	size_t			capacity;
	char			*(*at)(struct s_ft_str *this, size_t idx);
	char			*(*front)(struct s_ft_str *this);
	char			*(*back)(struct s_ft_str *this);
	int				(*empty)(struct s_ft_str *this);
	int				(*compare)(struct s_ft_str *this, struct s_ft_str *ftstr);
	void			(*clear)(struct s_ft_str *this);
	int				(*push_back)(struct s_ft_str *this, char c);
	int				(*resize)(struct s_ft_str *this, size_t size);
	struct s_ft_str	*(*join)(struct s_ft_str *this, struct s_ft_str *ftstr);
	struct s_ft_str	*(*substr)(struct s_ft_str *this, size_t strt, size_t size);
	int				(*append)(struct s_ft_str *this, char *cstr);
	int				(*add)(struct s_ft_str *this, struct s_ft_str *ftstr);
	char			*(*c_str)(struct s_ft_str *this);
	int				(*getline)(struct s_ft_str *this, int fd);
	int				(*getword)(struct s_ft_str *this, int fd);
}	t_ft_string;

#endif
