
#include "parser.h"

/*
	push_back until parser meet the operator token
*/
ast_node *parse_command(parser *self)
{
	ast_node *command;
	int cur_node_type;

	command = new_ast_node();
	if (command == NULL)
		return ast_malloc_error(command);
	command->pcmd = new std::vector<std::string>;
	if (command->pcmd == NULL)
		return ast_malloc_error(command);
	cur_node_type = get_prefix_node_type(self->pcur_token->type);
	if (cur_node_type == NODE_WORD)
		command->node_type = NODE_COMMAND;
	else
		return ast_syntax_error(command);
	command->pt = self->pcur_token;
	while (self->cur_idx < self->ptoken_stream->size() && cur_node_type == NODE_WORD)
	{
		command->pcmd->push_back(self->pcur_token->field);
		// if push_back failed, return ast_malloc_error
		move_next_token(self);
		cur_node_type = get_prefix_node_type(self->pcur_token->type);
	}
	return (command);
}
