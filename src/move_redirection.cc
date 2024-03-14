
#include "lexer.h"

static void pull_two_token_back(std::vector<token> *ptoken_stream, int from, int to)
{
	const token temp_token1 = (*ptoken_stream)[from];
	const token temp_token2 = (*ptoken_stream)[from + 1];
	int idx;

	idx = from;
	while (--idx >= to)
		(*ptoken_stream)[idx + 2] = (*ptoken_stream)[idx];
	(*ptoken_stream)[to] = temp_token1;
	(*ptoken_stream)[to + 1] = temp_token2;
}

static void pull_two_token_front(std::vector<token> *ptoken_stream, int from, int to)
{
	const token temp_token1 = (*ptoken_stream)[from];
	const token temp_token2 = (*ptoken_stream)[from + 1];
	int idx;

	idx = from - 1;
	while (++idx < to)
		(*ptoken_stream)[idx] = (*ptoken_stream)[idx + 2];
	(*ptoken_stream)[to] = temp_token1;
	(*ptoken_stream)[to + 1] = temp_token2;
}

void move_redirection_token(std::vector<token> *ptoken_stream)
{
	int to;
	int idx;

	idx = 0;
	to = 0;
	while (++idx < ptoken_stream->size() - 1)
		if ((*ptoken_stream)[idx].type == RDICT_READ || (*ptoken_stream)[idx].type == RDICT_HEREDOC)
		{
			pull_two_token_front(ptoken_stream, idx, to);
			to += 2;
		}
	idx = ptoken_stream->size() - 2;
	to = ptoken_stream->size() - 2;
	while (--idx >= 0)
		if ((*ptoken_stream)[idx].type == RDICT_WRITE || (*ptoken_stream)[idx].type == RDICT_APPEND)
		{
			pull_two_token_back(ptoken_stream, idx, to);
			to -= 2;
		}
}
