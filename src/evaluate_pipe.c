/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:35:17 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:35:19 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	evaluate_infix_pipe(t_loader *ld, const t_ast_node *node)
{
	// create pipe
	// init ld with newly created pipe
	// evaluate left
	evaluate_ast(ld, node->left);
	// evaluate right
	evaluate_ast(ld, node->right);
	// return status code of child process
}
