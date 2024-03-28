
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
