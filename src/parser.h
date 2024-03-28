/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:55:51 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/28 13:52:27 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./ft_vector/ft_vector.h"
# include "lexer.h"

enum					e_precedence
{
	P_NO_MATCH,
	P_LOWEST,
	P_LOGIC,
	P_PIPE,
	P_RDICT,
	P_PREFIX
};

int						get_precedence(int token_type);

enum					e_node_type
{
	NODE_ERROR,
	NODE_WORD,
	NODE_COMMAND,
	NODE_FILE,
	EXP_SUBSHELL,
	EXP_IN_PIPE,
	EXP_IN_AND,
	EXP_IN_OR,
	EXP_IN_RWRITE,
	EXP_IN_RAPPEND,
	EXP_PRE_RREAD,
	EXP_PRE_RHEREDOC,
	EXP_PRE_RWRITE,
	EXP_PRE_RAPPEND
};

int						get_prefix_node_type(int token_type);
int						get_infix_node_type(int token_type);

typedef struct s_ast_node
{
	t_token				*pt;
	char				**pcmd;
	int					node_type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

t_ast_node				*new_ast_node(void);
void					delete_ast_node(t_ast_node *self);

char					**new_cmd_list(int num_cmd);
void					delete_cmd_list(char **self);

typedef struct s_parser
{
	t_ft_vector			*ptoken_stream;
	int					cur_idx;
	t_token				*pcur_token;
	t_token				*pnext_token;
}						t_parser;

t_parser				*new_parser(t_ft_vector *ptstream);
void					delete_parser(t_parser *self);
void					move_next_token(t_parser *self);

t_ast_node				*parse(t_ft_vector *ptoken_stream);
t_ast_node				*parse_expression(t_parser *self, int precede);
t_ast_node				*parse_parenthesis(t_parser *self);
t_ast_node				*parse_prefix(t_parser *self);
t_ast_node				*parse_infix(t_parser *self, t_ast_node *left);
t_ast_node				*parse_command(t_parser *self);
t_ast_node				*parse_file(t_parser *self);

t_ast_node				*ast_syntax_error(t_ast_node *tree);
t_ast_node				*ast_malloc_error(t_ast_node *tree);

#endif
