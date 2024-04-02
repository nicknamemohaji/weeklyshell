/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:35:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/02 18:34:33 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <unistd.h>

int	evaluate_infix_pipe(t_loader *ld, const t_ast_node *node)
{
	int cur_pipe[2];

	// create pipe
	// init ld with newly created pipe
	pipe(cur_pipe);
	ld->next_read_fd = cur_pipe[0];
	ld->cur_write_fd = cur_pipe[1];
	// evaluate left
	evaluate_ast(ld, node->left);
	// evaluate right
	evaluate_ast(ld, node->right);
	// return status code of child process
}
