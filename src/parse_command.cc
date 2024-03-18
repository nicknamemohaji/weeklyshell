
#include "parser.h"

/*
	push_back until parser meet the operator token
*/
ast_node *parse_command(parser *self)
{
	ast_node *command;
	int next_node_type;

	command = new_ast_node();
	if (command == NULL)
		return ast_malloc_error(command);
	command->pcmd = new std::vector<std::string>;
	if (command->pcmd == NULL)
		return ast_malloc_error(command);
	command->node_type = NODE_COMMAND;
	command->pt = self->pcur_token;
	while (true)
	{
		command->pcmd->push_back(self->pcur_token->field);
		// if push_back failed, return ast_malloc_error
		next_node_type = get_prefix_node_type(self->pnext_token->type);
		if (next_node_type != NODE_WORD)
			break;
		move_next_token(self);
	}
	return (command);
}
