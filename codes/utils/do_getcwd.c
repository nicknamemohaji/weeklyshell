/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:30:40 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/09 15:21:19 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*do_getcwd_f(char *buf, size_t size);

char	*do_getcwd_f(char *buf, size_t size)
{
	char	*ret;

	ret = getcwd(buf, size);
	if (ret != NULL)
		return (ret);
	write(2, "[WARN] cwd not found. going up...\n", 34);
	if (chdir("..") != 0)
		exit(EXIT_FAILURE);
	return (do_getcwd_f(buf, size));
}
