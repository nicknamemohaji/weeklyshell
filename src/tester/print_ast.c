
#include "print_ast.h"
#include <stdio.h>

static void	print_tabs(int depth)
{
	for (int i = 0; i < depth; ++i)
		printf("\t");
}

static const char	*print_node_type(int ntype)
{
	if (ntype == NODE_ERROR)
		return ("NODE_ERROR");
	else if (ntype == NODE_WORD)
		return ("NODE_WORD");
	else if (ntype == NODE_COMMAND)
		return ("NODE_COMMAND");
	else if (ntype == NODE_FILE)
		return ("NODE_FILE");
	else if (ntype == EXP_SUBSHELL)
		return ("EXP_SUBSHELL");
	else if (ntype == EXP_IN_PIPE)
		return ("EXP_IN_PIPE");
	else if (ntype == EXP_IN_AND)
		return ("EXP_IN_AND");
	else if (ntype == EXP_IN_OR)
		return ("EXP_IN_OR");
	else if (ntype == EXP_IN_RWRITE)
		return ("EXP_IN_RWRITE");
	else if (ntype == EXP_IN_RAPPEND)
		return ("EXP_IN_RAPPEND");
	else if (ntype == EXP_PRE_RREAD)
		return ("EXP_PRE_RREAD");
	else if (ntype == EXP_PRE_RHEREDOC)
		return ("EXP_PRE_RHEREDOC");
	else if (ntype == EXP_PRE_RWRITE)
		return ("EXP_PRE_RWRITE");
	else
		return ("EXP_PRE_RAPPEND");
}

void	print_ast(t_ast_node *tree, int depth)
{
	printf("\n");
	print_tabs(depth);
	printf("node type : %s\n", print_node_type(tree->node_type));
	if (tree->node_type == NODE_COMMAND || tree->node_type == NODE_FILE)
	{
		print_tabs(depth);
		printf("print command : ");
		for (int i = 0; tree->pcmd[i] != NULL; ++i)
		{
			printf("%s ", tree->pcmd[i]);
		}
		printf("\n");
	}
	print_tabs(depth);
	printf("left node");
	if (tree->left == NULL)
		printf("-> NULL\n");
	else
		print_ast(tree->left, depth + 1);
	print_tabs(depth);
	printf("right node");
	if (tree->right == NULL)
		printf("-> NULL\n");
	else
		print_ast(tree->right, depth + 1);
	printf("\n");
}
