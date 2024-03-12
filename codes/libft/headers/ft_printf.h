/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:49:46 by kyungjle          #+#    #+#             */
/*   Updated: 2024/01/03 18:54:29 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_buf {
	int				buf_len;
	char			*buf;
	struct s_buf	*next;
}	t_buf;

// ft_printf.c
int		ft_printf(const char *s, ...);
int		ft_sprintf_va(const char *s, char **buf, va_list va);
int		ft_sprintf(char	*ret, const char *s, ...);

// fp_conversion_charater.c
char	*fp_char(char c);
char	*fp_string(char *s);

// fp_conversion_other.c
char	*fp_ptr(void *p);
char	*fp_percent(void);

// fp_conversion_integer.c
char	*fp_integer_base10_signed(long n);
char	*fp_integer_base10_unsigned(unsigned long n);
char	*fp_integer_base16(unsigned long n, int is_upper);

// fp_conversion_wrapper.c
int		fp_valid_conversion(char *s);
char	*fp_conversion(int flag, int width, char conversion, va_list va);

// fp_list.c
t_buf	*fp_new_list(void);
t_buf	*fp_new_node(char *s, char *conv);
int		fp_free_list(t_buf *list);
int		fp_list_join(t_buf *list, char **buf);
char	*fp_join_buf(char *str_buf, int str_buf_len, t_buf *buf);

// fp_parse.c
char	*fp_parse_format(const char **s, va_list va, char *conv);
char	*fp_parse_normal(const char **s);

#endif