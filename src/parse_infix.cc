
#include "parser.h"

ast_node *parse_infix(parser *self, ast_node *left)
{
	ast_node *exp;
	int precede;

	// create expression node(operator)
	exp = new_ast_node();
	if (exp == NULL)
		return ast_malloc_error(left);
	exp->node_type = get_infix_node_type(self->pcur_token->type);
	exp->pt = self->pcur_token;
	exp->left = left;
	precede = get_precedence(self->pcur_token->type);
	move_next_token(self);
	exp->right = parse_expression(self, precede);
	if (exp->right == NULL)
	{
		delete_ast_node(exp);
		exp = NULL;
	}
	return exp;
}
