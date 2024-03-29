
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

static const char	*print_tok_type(int ttype)
{
	if (ttype == ILLEGAL)
		return ("ILLEGAL");
	else if (ttype == LPAR)
		return ("LPAR");
	else if (ttype == RPAR)
		return ("RPAR");
	else if (ttype == PIPE)
		return ("PIPE");
	else if (ttype == RDICT_READ)
		return ("RDICT_READ");
	else if (ttype == RDICT_WRITE)
		return ("RDICT_WRITE");
	else if (ttype == OPRT_AND)
		return ("OPRT_AND");
	else if (ttype == OPRT_OR)
		return ("OPRT_OR");
	else if (ttype == RDICT_HEREDOC)
		return ("RDICT_HEREDOC");
	else if (ttype == RDICT_APPEND)
		return ("RDICT_APPEND");
	else if (ttype == KEY_ECHO)
		return ("KEY_ECHO");
	else if (ttype == KEY_CD)
		return ("KEY_CD");
	else if (ttype == KEY_PWD)
		return ("KEY_PWD");
	else if (ttype == KEY_EXPORT)
		return ("KEY_EXPORT");
	else if (ttype == KEY_UNSET)
		return ("KEY_UNSET");
	else if (ttype == KEY_ENV)
		return ("KEY_ENV");
	else if (ttype == KEY_EXIT)
		return ("KEY_EXIT");
	else
		return ("IDENT");
}

void	print_ast(t_ast_node *tree, int depth)
{
	printf("\n");
	print_tabs(depth);
	printf("node type : %s\n", print_node_type(tree->node_type));
	print_tabs(depth);
	printf("token type : %s\n", print_tok_type(tree->pt->type));
	print_tabs(depth);
	printf("token field : %s\n", tree->pt->field.c_str(&tree->pt->field));
	if (tree->node_type == NODE_COMMAND)
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
