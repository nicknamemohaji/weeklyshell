/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:34:51 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/02 19:28:46 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	execute_command(t_loader *ld, const t_ast_node *node)
{
	int pid;

	// expand
	// detact built-in and run
	if (/*TBD, is_built_in*/)
		return (/*TBD, build-in*/);
	pid = fork();
	if (pid == 0)
	{
		// child, redirection
		close(ld->next_read_fd);
		if ()
			dup2();
		if ()
			dup2();
		// execve
	}
	// parent, close used fd
	close(ld->cur_read_fd);
	close(ld->cur_write_fd);
	// parent, set fd
	ld->cur_read_fd = ld->next_read_fd;
	ld->cur_write_fd = -1;
	ld->next_read_fd = -1;
	// save child pid, push back
	if (ld->p_pid_vec->push_back(ld->p_pid_vec, &pid) == 0)
	{
		// malloc error
	}
}
