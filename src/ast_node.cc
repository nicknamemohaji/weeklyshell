
#include "parser.h"

ast_node *new_ast_node()
{
	ast_node *pnode;

	pnode = new ast_node;
	pnode->pcmd = NULL;
	pnode->left = NULL;
	pnode->right = NULL;
	return (pnode);
}

void delete_ast_node(ast_node *self)
{
	if (self == NULL)
		return;
	if (self->left != NULL)
		delete_ast_node(self->left);
	if (self->right != NULL)
		delete_ast_node(self->right);
	delete self->pcmd;
	delete self;
}
