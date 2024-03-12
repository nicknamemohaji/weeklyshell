/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fp_conversion_character.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:00:56 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/24 01:37:35 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fp_char(char c);
char	*fp_string(char *s);

char	*fp_char(char c)
{
	char	*ret;

	ret = malloc(2 * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

char	*fp_string(char *s)
{
	if (s == NULL)
		return (ft_strdup("(null)"));
	else
		return (ft_strdup(s));
}
