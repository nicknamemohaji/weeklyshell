/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:08:32 by kyungjle          #+#    #+#             */
/*   Updated: 2024/01/03 19:45:51 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...);
int	ft_sprintf(char	*ret, const char *s, ...);
int	ft_sprintf_va(const char *s, char **buf, va_list va);

int	ft_printf(const char *s, ...)
{
	int		ret;
	char	*buf;
	va_list	va;

	if (*s == 0)
		return (0);
	buf = NULL;
	va_start(va, s);
	ret = ft_sprintf_va(s, &buf, va);
	va_end(va);
	if (ret < 0)
		return (ret);
	write(1, buf, ret);
	free(buf);
	return (ret);
}

int	ft_sprintf(char	*ret, const char *s, ...)
{
	int		len;
	char	*buf;
	va_list	va;

	if (*s == 0)
		return (0);
	buf = NULL;
	va_start(va, s);
	len = ft_sprintf_va(s, &buf, va) + 1;
	va_end(va);
	if (len < 0)
		return (-1);
	ft_strlcat(ret, buf, len + 1);
	free(buf);
	return (len);
}

/*
 * ft_sprintf_va: it is caller's responsibiltity to call va_end
 */
int	ft_sprintf_va(const char *s, char **buf, va_list va)
{
	t_buf	*list_start;
	t_buf	*last_node;
	t_buf	*new_node;
	int		len;
	char	conv;

	list_start = fp_new_list();
	if (list_start == NULL)
		return (-1);
	last_node = list_start;
	while (*s != 0)
	{
		if (*s == '%' && fp_valid_conversion((char *) s))
			new_node = fp_new_node(fp_parse_format(&s, va, &conv), &conv);
		else
			new_node = fp_new_node(fp_parse_normal(&s), NULL);
		if (new_node == NULL)
			return (fp_free_list(list_start));
		last_node->next = new_node;
		last_node = last_node->next;
	}
	len = fp_list_join(list_start->next, buf);
	fp_free_list(list_start);
	return (len);
}
