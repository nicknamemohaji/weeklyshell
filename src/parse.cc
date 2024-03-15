
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
	p = new_parser(ptoken_stream);
	/*
		preprocessing required
		redirection 관련 처리를 위해서 redirection과 그에 따르는 word하나를 다른 연산자 만나기 전까지 밀어낸다.
		즉 swap을 반복한다.
	*/
	if (is_lexical_error(ptoken_stream))
	{
		delete_parser(p);
		return ast_syntax_error(NULL);
	}
	move_redirection_token(ptoken_stream);
	end_token.type = END;
	ptoken_stream->push_back(end_token);
	tree = parse_expression(p, LOWEST);
	// parse expression
	delete_parser(p);
	return tree;
}
