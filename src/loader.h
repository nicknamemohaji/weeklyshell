/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:20:33 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 19:20:37 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include "./ft_string/ft_string.h"
# include "parser.h"

typedef struct s_loader
{
	int		cur_read_fd;
	int		cur_write_fd;
	int		next_read_fd;
}			t_loader;

t_loader	*new_loader(void);
void		delete_loader(t_loader *self);

// evaluate ast node
// identify type of ast_node and call proper evaluator
// return int to show error
int			evaluate_ast(t_loader *ld, const t_ast_node *node);

// expression evaluator, derived
int			evaluate_subshell(t_loader *ld, const t_ast_node *node);
int			evaluate_infix_pipe(t_loader *ld, const t_ast_node *node);
int			evaluate_infix_and(t_loader *ld, const t_ast_node *node);
int			evaluate_infix_or(t_loader *ld, const t_ast_node *node);
int			evaluate_infix_rwrite(t_loader *ld, const t_ast_node *node);
int			evaluate_infix_rappend(t_loader *ld, const t_ast_node *node);
int			evaluate_prefix_rread(t_loader *ld, const t_ast_node *node);
int			evaluate_prefix_rheredoc(t_loader *ld, const t_ast_node *node);
int			evaluate_prefix_rwrite(t_loader *ld, const t_ast_node *node);
int			evaluate_prefix_rappend(t_loader *ld, const t_ast_node *node);

// execute command
int			execute_command(t_loader *ld, const t_ast_node *node);

#endif
