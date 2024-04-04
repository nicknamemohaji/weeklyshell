/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:45:00 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:45:03 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

t_ast_node	*ast_syntax_error(t_ast_node *tree)
{
	write(1, "Syntax Error.\n", 14);
	delete_ast_node(tree);
	return (NULL);
}

t_ast_node	*ast_malloc_error(t_ast_node *tree)
{
	write(1, "Memory Allocation Failure.\n", 27);
	delete_ast_node(tree);
	return (NULL);
}
