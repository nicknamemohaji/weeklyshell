
#include "parser.h"

/*
	subshell

	create subshell node as a root of subtree
*/
ast_node *parse_parenthesis(parser *self)
{
	ast_node *subshell;

	move_next_token(self);
	subshell = new_ast_node();
	if (subshell == NULL)
		return ast_malloc_error(subshell);
	subshell->node_type = EXP_SUBSHELL;
	subshell->pt = self->pcur_token;
	subshell->left = parse_expression(self, LOWEST);
	if (subshell->left != NULL || self->pcur_token->type != RPAR)
		return (ast_syntax_error(subshell));
	return subshell;
}
