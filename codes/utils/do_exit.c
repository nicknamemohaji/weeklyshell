/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:23:16 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/21 17:28:58 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	do_exit(char *errorstr);

/*
void	do_exit(char *errorstr)
:param errorstr: debug info to print on STDERR

Wrapper function to print errno message and exit on unrecovable errors
*/
void	do_exit(char *errorstr)
{
	perror(errorstr);
	exit(EXIT_FAILURE);
}
