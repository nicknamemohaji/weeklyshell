
#include <iostream>
#include "parser.h"

/*
	input : pointer of token stream, result of lexing.
	result : root node of abstract syntax tree.

	return NULL if syntax error.
*/
ast_node *parse(std::vector<token> *ptoken_stream)
{
	parser *p;
	ast_node *tree;
	token end_token;

	// create parser
	move_redirection_token(ptoken_stream);
	end_token.type = END;
	ptoken_stream->push_back(end_token);
	p = new_parser(ptoken_stream);
	tree = parse_expression(p, P_LOWEST);
	// parse expression
	delete_parser(p);
	return tree;
}
