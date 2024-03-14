
#include "parser.h"
#include <iostream>

ast_node *ast_syntax_error(ast_node *tree)
{
	std::cout << "Syntax Error.\n";
	delete_ast_node(tree);
	return NULL;
}

ast_node *ast_malloc_error(ast_node *tree)
{
	std::cout << "Memory Allocation Failure.\n";
	delete_ast_node(tree);
	return NULL;
}
