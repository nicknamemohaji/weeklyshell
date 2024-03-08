
#include <string>

// 노드의 타입에 대한 열거형
// 루트 노드 식별을 위한 expression 타입
// operator : |, &&, ||, <, <<, >, >>
// expandable : *, $XXX, ...

typedef struct ast_node
{
	int type;
	std::string field;
	ast_node *left; // 둘 다 nullptr이면 leaf
	ast_node *right;
} ast;
