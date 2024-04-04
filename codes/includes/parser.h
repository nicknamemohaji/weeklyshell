/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:55:51 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/04 11:18:37 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_vector.h"
# include "lexer.h"

// ========================= operator precedence =====================//
/*
	precedence of operators.

	value of the enumerator shows it's precedence.
*/
enum					e_precedence
{
	P_NO_MATCH,
	P_LOWEST,
	P_LOGIC,
	P_PIPE,
	P_RDICT,
	P_PREFIX
};

// get enum of precedence from token's type
int						get_precedence(int token_type);

// ========================= Abstract Syntax Tree =====================//
/*
	type of node in abstract syntax tree.
	each nodes are either expression or command + args or name of file.
*/
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

// get node's type from token's type.
int						get_prefix_node_type(int token_type);
int						get_infix_node_type(int token_type);

/*
	node of abstract syntax tree.

	binary tree.
*/
typedef struct s_ast_node
{
	char				**pcmd;
	enum e_node_type	node_type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

// constructor and destructor for ast_node
t_ast_node				*new_ast_node(void);
void					delete_ast_node(t_ast_node *self);

// constructor and destructor for cmd_list
// cmd_list is an c-style array of c-style string
char					**new_cmd_list(int num_cmd);
void					delete_cmd_list(char **self);

// ========================= Parser =====================//
/*
	parser object.

	parser object to create ast.
	traverse token stream with this object.
*/
typedef struct s_parser
{
	t_ft_vector			*ptoken_stream;
	int					cur_idx;
	t_token				*pcur_token;
	t_token				*pnext_token;
}						t_parser;

// constructor and destructor for parser object.
t_parser				*new_parser(t_ft_vector *ptstream);
void					delete_parser(t_parser *self);

// method of parser, move currently pointing token in token stream.
void					move_next_token(t_parser *self);

/*
	parse function.

	will be called to create ast.
	constructor of ast.

	to destruct ast, call delete_ast_node().
*/
t_ast_node				*parse_f(const char *cstr);

// method of parser, parse each token and return ast_node
t_ast_node				*parse_expression(t_parser *self, int precede);
t_ast_node				*parse_parenthesis(t_parser *self);
t_ast_node				*parse_prefix(t_parser *self);
t_ast_node				*parse_infix(t_parser *self, t_ast_node *left);
t_ast_node				*parse_command(t_parser *self);
t_ast_node				*parse_file(t_parser *self);

/*
	error handler.

	print error message and call delete_ast_node().
*/
t_ast_node				*ast_syntax_error(t_ast_node *tree);
t_ast_node				*ast_malloc_error(t_ast_node *tree);

// ====================================================//

#endif
