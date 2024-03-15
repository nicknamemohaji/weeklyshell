
#include <iostream>
#include "print_ast.h"

static void print_tabs(int depth)
{
	for (int i = 0; i < depth; ++i)
		std::cout << '\t';
}

static const std::string print_node_type(int ntype)
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

static const std::string print_tok_type(int ttype)
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

void print_ast(ast_node *tree, int depth)
{
	std::cout << '\n';
	print_tabs(depth);
	std::cout << "node type : " << print_node_type(tree->node_type) << '\n';
	print_tabs(depth);
	std::cout << "token type : " << print_tok_type(tree->pt->type) << '\n';
	print_tabs(depth);
	std::cout << "token field : " << tree->pt->field << '\n';
	if (tree->node_type == NODE_COMMAND)
	{
		print_tabs(depth);
		std::cout << "print command : ";
		for (const std::string &str : *tree->pcmd)
		{
			std::cout << str << ' ';
		}
		std::cout << '\n';
	}
	print_tabs(depth);
	std::cout << "left node";
	if (tree->left == NULL)
		std::cout << "-> NULL\n";
	else
		print_ast(tree->left, depth + 1);
	print_tabs(depth);
	std::cout << "right node";
	if (tree->right == NULL)
		std::cout << "-> NULL\n";
	else
		print_ast(tree->right, depth + 1);
	std::cout << '\n';
}
