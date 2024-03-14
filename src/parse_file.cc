
#include "parser.h"

// get single word as a file node
ast_node *parse_file(parser *self)
{
	ast_node *file;

	move_next_token(self);
	if (self->cur_idx == self->ptoken_stream->size())
		return ast_syntax_error(file);
	file = new_ast_node();
	if (file == NULL)
		return ast_malloc_error(file);
	file->node_type = get_prefix_node_type(self->pcur_token->type);
	if (file->node_type != NODE_WORD)
		return ast_syntax_error(file);
	file->node_type = NODE_FILE;
	file->pt = self->pcur_token;
	return (file);
}
