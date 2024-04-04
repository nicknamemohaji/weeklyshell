/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:47:43 by dogwak            #+#    #+#             */
/*   Updated: 2023/12/21 19:22:38 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * C++ like , norminette compatible string container.
 * do not use this code with c++ runtime.

	made by dogwak.
*/

#ifndef FT_STRING_H
# define FT_STRING_H

# include "ft_string_struct.h"

/*
class t_ft_str
{
	size_t			size;
	char			*at(struct s_ft_str *this, size_t idx);
	char			*front(struct s_ft_str *this);
	char			*back(struct s_ft_str *this);
	int				empty(struct s_ft_str *this);
	int				compare(struct s_ft_str *this, struct s_ft_str *ftstr);
	void			clear(struct s_ft_str *this);
	int				push_back(struct s_ft_str *this, char c);
	int				resize(struct s_ft_str *this, size_t size);
	struct s_ft_str	*copy(t_ft_string *this);
	struct s_ft_str	*join(struct s_ft_str *this, struct s_ft_str *ftstr);
	struct s_ft_str	*substr(struct s_ft_str *this, size_t strt, size_t size);
	int				append(t_ft_string *this, char *cstr);
	int				add(t_ft_string *this, t_ft_string *ftstr);
	int				*c_str(struct s_ft_str *this);
	int				getline(struct s_ft_str *this, int fd);
	int				getword(struct s_ft_str *this, int fd);
};
*/

t_ft_string	construct_ftstr(void);
t_ft_string	construct_ftstr_len(size_t len);
t_ft_string	construct_ftstr_cstr(char *cstr);
t_ft_string	construct_ftstr_copy(t_ft_string *ftstr);
void		destruct_ftstr(t_ft_string *ftstr);

t_ft_string	*new_ftstr(void);
t_ft_string	*new_ftstr_len(size_t len);
t_ft_string	*new_ftstr_cstr(char *cstr);
t_ft_string	*new_ftstr_copy(t_ft_string *ftstr);
void		delete_ftstr(t_ft_string *ftstr);

#endif
