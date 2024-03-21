
#include <vector>
#include "lexer.h"

enum precedence
{
	P_NO_MATCH,
	P_LOWEST,
	P_PIPE,
	P_LOGIC,
	P_RDICT,
	P_PREFIX
};

int get_precedence(int token_type);

// 노드의 타입에 대한 열거형
// 루트 노드 식별을 위한 expression 타입
// operator : |, &&, ||, <, <<, >, >>
// expandable : *, $XXX, ...

enum node_type
{
	NODE_ERROR,
	NODE_WORD,
	NODE_COMMAND,
	NODE_FILE,
	EXP_SUBSHELL,
	EXP_IN_PIPE,
	EXP_IN_AND,
	EXP_IN_OR,
	EXP_IN_RWRITE,
	EXP_IN_RAPPEND,
	EXP_PRE_RREAD,
	EXP_PRE_RHEREDOC,
	EXP_PRE_RWRITE,
	EXP_PRE_RAPPEND
};

int get_prefix_node_type(int token_type);
int get_infix_node_type(int token_type);

typedef struct ast_node
{
	token *pt;
	std::vector<std::string> *pcmd; // supposed to be char **
	int node_type;
	ast_node *left; // 둘 다 nullptr이면 leaf
	ast_node *right;
} ast_node;

ast_node *new_ast_node();
void delete_ast_node(ast_node *self);

typedef struct parser
{
	std::vector<token> *ptoken_stream;
	int cur_idx;
	token *pcur_token;
	token *pnext_token;
} parser;

parser *new_parser(std::vector<token> *ptstream);
void delete_parser(parser *self);
void move_next_token(parser *self);

ast_node *parse(std::vector<token> *ptoken_stream);
ast_node *parse_expression(parser *self, int precede);
ast_node *parse_parenthesis(parser *self);
ast_node *parse_prefix(parser *self);
ast_node *parse_infix(parser *self, ast_node *left);
ast_node *parse_command(parser *self);
ast_node *parse_file(parser *self);

ast_node *ast_syntax_error(ast_node *tree);
ast_node *ast_malloc_error(ast_node *tree);
