/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:09:02 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 10:23:08 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf	*fp_new_list(void);
t_buf	*fp_new_node(char *s, char *conv);
int		fp_free_list(t_buf *list);
int		fp_list_join(t_buf *list, char **buf);
char	*fp_join_buf(char *str_buf, int str_buf_len, t_buf *buf);

int	fp_free_list(t_buf *list)
{
	t_buf	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		if (temp->buf != NULL)
			free(temp->buf);
		free(temp);
	}
	return (-1);
}

/*
 * note that in fp_sprintf_va, first node of list is pointing NULL as buffer,
 * while fp_list_join expects valid buffer node.
 */
int	fp_list_join(t_buf *list, char **buf)
{
	char	*ret;
	char	*temp;
	int		len;

	len = list->buf_len;
	ret = ft_calloc(list->buf_len + 1, sizeof(char));
	if (ret == NULL)
		return (-1);
	ft_memcpy(ret, list->buf, list->buf_len);
	list = list->next;
	while (list != NULL)
	{
		temp = fp_join_buf(ret, len, list);
		free(ret);
		if (temp == NULL)
			return (-1);
		ret = temp;
		len += list->buf_len;
		list = list->next;
	}
	*buf = ret;
	return (len);
}

char	*fp_join_buf(char *str_buf, int str_buf_len, t_buf *buf)
{
	char	*ret;

	ret = ft_calloc(str_buf_len + buf->buf_len + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (buf->buf == NULL)
		return (NULL);
	ft_memcpy(ret, str_buf, str_buf_len);
	ft_memcpy((ret + str_buf_len), buf->buf, buf->buf_len);
	return (ret);
}

t_buf	*fp_new_list(void)
{
	t_buf	*new_list;

	new_list = malloc(1 * sizeof(t_buf));
	if (new_list == NULL)
		return (NULL);
	new_list->buf = NULL;
	new_list->next = NULL;
	return (new_list);
}

t_buf	*fp_new_node(char *s, char *conv)
{
	t_buf	*new_list;

	if (s == NULL)
		return (NULL);
	new_list = malloc(1 * sizeof(t_buf));
	if (new_list == NULL)
	{
		free(s);
		return (NULL);
	}
	new_list->buf = s;
	new_list->buf_len = ft_strlen(s);
	if (new_list->buf_len == 0 && conv != NULL && *conv == 'c')
		new_list->buf_len += 1;
	new_list->next = NULL;
	return (new_list);
}
