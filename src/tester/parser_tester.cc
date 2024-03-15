
/*
g++ -g parser_tester.cc print_ast.cc ../ast_node.cc ../get_node_type.cc ../get_precedence.cc ../get_token_type.cc ../get_token.cc ../is_lexical_error.cc ../lexer.cc ../move_redirection.cc ../parse_command.cc ../parse_expression.cc ../parse_file.cc ../parse_infix.cc ../parse_parenthesis.cc ../parse_prefix.cc ../parse.cc ../parser_error.cc ../parser.cc -o parser_tester
*/
#include <iostream>
#include <array>
#include "print_ast.h"

std::array<std::string, 21> token_type =
	{
		"ILLEGAL ", " LPAR ", " RPAR ", " PIPE ", " RDICT_READ ", " RDICT_WRITE ", " OPRT_AND ", " OPRT_OR ", " RDICT_HEREDOC ", " RDICT_APPEND ", " KEY_ECHO ", " KEY_CD ", " KEY_PWD ", " KEY_EXPORT ", " KEY_UNSET ", " KEY_ENV ", " KEY_EXIT ", " IDENT "};

void print_token(const std::vector<token> &token_stream)
{
	for (const token &t : token_stream)
	{
		std::cout << token_type[t.type] << t.field << '\n';
	}
}

int main()
{
	std::string input_str;
	std::vector<token> token_stream;

	while (true)
	{
		if (std::cin.eof())
			break;
		std::getline(std::cin, input_str);
		ast_node *tree;
		// lexing
		token_stream = tokenize(input_str.c_str());
		std::cout << "=== token stream before sorted ===\n";
		print_token(token_stream);
		// move redirection
		move_redirection_token(&token_stream);
		std::cout << "=== token stream  after sorted ===\n";
		print_token(token_stream);
		// parsing
		std::cout << "====== parse Abstract Symbol Tree ======\n";
		tree = parse(&token_stream);
		if (tree == NULL)
			return 0;
		std::cout << "done.\n";
		std::cout << "====== print Abstract Symbol Tree ======\n";
		print_ast(tree, 0);
		delete_ast_node(tree);
		//
	}
}
