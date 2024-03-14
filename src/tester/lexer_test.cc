// g++ -g ../lexer_test.cc ../get_token_type.cc ../get_token.cc ../lexer.cc -o lexer_tester
#include <iostream>
#include <array>
#include "../lexer.h"

std::array<std::string, 21> token_type =
	{
		"ILLEGAL ", " LPAR ", " RPAR ", " PIPE ", " RDICT_READ ", " RDICT_WRITE ", " OPRT_AND ", " OPRT_OR ", " RDICT_HEREDOC ", " RDICT_APPEND ", " KEY_ECHO ", " KEY_CD ", " KEY_PWD ", " KEY_EXPORT ", " KEY_UNSET ", " KEY_ENV ", " KEY_EXIT ", " IDENT "};
int main()
{
	std::string test_input;
	std::getline(std::cin, test_input);
	std::vector<token> token_stream = tokenize(test_input.c_str());
	for (const token &t : token_stream)
	{
		std::cout << token_type[t.type] << t.field << '\n';
	}
}
