
#include "parser.h"

ast_node *parse_prefix(parser *self)
{
	ast_node *exp;
	int node_type;

	node_type = get_prefix_node_type(self->pcur_token->type);
	if (node_type == NODE_ERROR)
		return ast_syntax_error(NULL);
	else if (self->pcur_token->type == LPAR)
		return parse_parenthesis(self);
	else if (node_type == NODE_WORD)
		return parse_command(self);
	exp = new_ast_node();
	if (exp == NULL)
		return ast_malloc_error(exp);
	exp->node_type = node_type;
	exp->pt = self->pcur_token;
	move_next_token(self);
	exp->left = parse_file(self);
	move_next_token(self);
	exp->right = parse_expression(self, PREFIX);
	if (exp->left == NULL || exp->right == NULL)
	{
		delete_ast_node(exp);
		exp = NULL;
	}
	return (exp);
}
