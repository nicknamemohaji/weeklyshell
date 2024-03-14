
#include "lexer.h"

static int is_tok_operator(std::vector<token> *ptoken_stream, int idx)
{
	const int cur_tok_type = (*ptoken_stream)[idx].type;

	return ((PIPE <= cur_tok_type) && (cur_tok_type <= RDICT_APPEND));
}

int is_lexical_error(std::vector<token> *ptoken_stream)
{
	int idx;
	int cur_tok_type;

	idx = -1;
	while (++idx < ptoken_stream->size() - 1)
	{
		if (is_tok_operator(ptoken_stream, idx) && is_tok_operator(ptoken_stream, idx + 1))
			return (1);
	}
	return (is_tok_operator(ptoken_stream, idx));
}
