
#include "parser.h"
#include <iostream>

ast_node *parse_expression(parser *self, int precede)
{
	ast_node *left_exp;
	int next_node_type;

	if (self->cur_idx == self->ptoken_stream->size())
		return ast_syntax_error(NULL);
	left_exp = parse_prefix(self);
	if (self->pcur_token->type == END)
		return (left_exp);
	while (left_exp != NULL && self->cur_idx < self->ptoken_stream->size() - 2 && precede < get_precedence(self->pnext_token->type))
	{
		next_node_type = get_infix_node_type(self->pnext_token->type);
		if (next_node_type == NODE_ERROR)
			return (ast_syntax_error(left_exp));
		else
		{
			move_next_token(self);
			left_exp = parse_infix(self, left_exp);
			if (left_exp == NULL)
				break;
		}
	}
	return (left_exp);
}
