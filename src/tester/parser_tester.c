
/*
g++
	-g parser_tester.cc print_ast.cc ../ast_node.cc ../get_node_type.cc ../get_precedence.cc ../get_token_type.cc ../get_token.cc ../is_lexical_error.cc ../lexer.cc ../move_redirection.cc ../parse_command.cc ../parse_expression.cc ../parse_file.cc ../parse_infix.cc ../parse_parenthesis.cc ../parse_prefix.cc ../parse.cc ../parser_error.cc ../parser.cc
	-o parser_tester
*/
#include "../ft_string/ft_string.h"
#include "print_ast.h"
#include <stdio.h>

const char	*token_type[21] = {"ILLEGAL ", " LPAR ", " RPAR ", " PIPE ",
		" RDICT_READ ", " RDICT_WRITE ", " OPRT_AND ", " OPRT_OR ",
		" RDICT_HEREDOC ", " RDICT_APPEND ", " KEY_ECHO ", " KEY_CD ",
		" KEY_PWD ", " KEY_EXPORT ", " KEY_UNSET ", " KEY_ENV ", " KEY_EXIT ",
		" IDENT ", "FILE_NAME "};

void	print_token(const t_ft_vector *token_stream)
{
	t_token	*htok_vec;

	htok_vec = (t_token *)(token_stream->pbuffer);
	for (size_t i = 0; i < token_stream->size; ++i)
	{
		printf("%s %s\n", token_type[htok_vec[i].type],
			htok_vec[i].field.c_str(&htok_vec[i].field));
	}
}

void	check_leak(void)
{
	system("leaks parser_tester");
}

int	main(void)
{
	t_ast_node	*tree;
	t_ft_string	input_str;
	t_ft_vector	*ptoken_stream;

	input_str = construct_ftstr();
	atexit(check_leak);
	while (1)
	{
		if (input_str.getline(&input_str, 0) == 0)
			break ;
		// lexing
		ptoken_stream = tokenize(input_str.c_str(&input_str));
		printf("=== token stream before sorted ===\n");
		print_token(ptoken_stream);
		// move redirection
		move_redirection_token(ptoken_stream);
		printf("=== token stream  after sorted ===\n");
		print_token(ptoken_stream);
		delete_ftvec(ptoken_stream);
		// parsing
		printf("====== parse Abstract Syntax Tree ======\n");
		tree = parse(input_str.c_str(&input_str));
		if (tree == NULL)
		{
			delete_ast_node(tree);
			destruct_ftstr(&input_str);
			return (0);
		}
		printf("done.\n ====== print Abstract Syntax Tree ======\n");
		print_ast(tree, 0);
		delete_ast_node(tree);
		//
	}
	destruct_ftstr(&input_str);
}
