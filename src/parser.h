
#include <string>
#include <vector>
#include "lexer.h"

enum precedence
{
	NO_MATCH,
	LOWEST,
	PIPE_AND_RDICT,
	LOGIC,
	PAREN,
	PREFIX
};

int get_precedence(int token_type);

// 노드의 타입에 대한 열거형
// 루트 노드 식별을 위한 expression 타입
// operator : |, &&, ||, <, <<, >, >>
// expandable : *, $XXX, ...

enum node_type
{
	COMMAND,
	EXP_IN_PIPE,
	EXP_IN_RREAD,
	EXP_IN_RHEREDOC,
	EXP_IN_RWRITE,
	EXP_IN_RAPPEND,
	EXP_IN_AND,
	EXP_IN_OR,
	EXP_PRE_RREAD,
	EXP_PRE_RHEREDOC
};

typedef struct ast_node
{
	token *pt;
	std::vector<std::string> cmd; // supposed to be char **
	int node_type;
	ast_node *left; // 둘 다 nullptr이면 leaf
	ast_node *right;
} ast_node;

ast_node *new_ast_node();
void delete_ast_node();

typedef struct parser
{
	std::vector<token> *ptoken_stream;
	int cur_idx;
	token *pcur_token;
	token *pnext_token;
} parser;

parser *new_parser(std::vector<token> *ptstream);
void delete_parser(parser *self);

void move_next(parser *self);

ast_node *parse_expression(parser *self, int precede);
ast_node *parse_parenthesis(parser *self, int precede);

ast_node *parse_prefix(parser *self, int precede);
ast_node *parse_infix(parser *self, int precede);

ast_node *parse_command(parser *self);
