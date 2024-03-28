/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:34:51 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:34:56 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	execute_command(t_loader *ld, const t_ast_node *node)
{
	/*
	// fork
	if ()
	{
		// child
		// close next read fd
		// execve
	}
	// parent
	// close cur read, cur write fd
	ld->cur_read_fd = -1;
	ld->cur_write_fd = -1;
	// move next fd
	if (ld->next_read_fd >= 0)
		ld->cur_read_fd = ld->next_read_fd;
	// TBD
	// expand words
	// TBD
	// check built-in command
	if (0)
	{
		// check single built-in command
		// handle built-in command
		// return (execute_built_in());
	}
	// get exit status?
	return (1);
	*/
}
