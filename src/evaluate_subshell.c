/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:35:10 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:35:13 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	evaluate_subshell(t_loader *ld, const t_ast_node *node)
{
	// fork and redirect stdin and stdout with current_fds
	// create new loader and call evaluate_ast()
	// return state of subshell child process
}
