
#include "lexer.h"

/*
	from < to
*/
static void pull_two_token_back(std::vector<token> *ptoken_stream, int from, int to)
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

/*
	to < from
*/
static void pull_two_token_front(std::vector<token> *ptoken_stream, int from, int to)
{
	const token temp_token1 = (*ptoken_stream)[from];
	const token temp_token2 = (*ptoken_stream)[from + 1];
	int idx;

	idx = from + 2;
	while (--idx > to + 1)
		(*ptoken_stream)[idx] = (*ptoken_stream)[idx - 2];
	(*ptoken_stream)[to] = temp_token1;
	(*ptoken_stream)[to + 1] = temp_token2;
}

static void move_left_redirect(std::vector<token> *ptoken_stream)
{
	int to;
	int idx;

	idx = -1;
	to = 0;
	while (++idx < ptoken_stream->size() - 1)
	{
		if ((*ptoken_stream)[idx].type == RDICT_READ || (*ptoken_stream)[idx].type == RDICT_HEREDOC)
		{
			pull_two_token_front(ptoken_stream, idx, to);
			to += 2;
		}
		else if ((*ptoken_stream)[idx].type == PIPE || (*ptoken_stream)[idx].type == LPAR || (*ptoken_stream)[idx].type == RPAR || (*ptoken_stream)[idx].type == OPRT_AND || (*ptoken_stream)[idx].type == OPRT_OR)
			to = idx + 1;
	}
}

static void move_right_redirect(std::vector<token> *ptoken_stream)
{
	int to;
	int idx;

	idx = ptoken_stream->size() - 0;
	to = ptoken_stream->size() - 2;
	while (--idx >= 0)
	{
		if ((*ptoken_stream)[idx].type == RDICT_WRITE || (*ptoken_stream)[idx].type == RDICT_APPEND)
		{
			pull_two_token_back(ptoken_stream, idx, to);
			to -= 2;
		}
		else if ((*ptoken_stream)[idx].type == PIPE || (*ptoken_stream)[idx].type == LPAR || (*ptoken_stream)[idx].type == RPAR || (*ptoken_stream)[idx].type == OPRT_AND || (*ptoken_stream)[idx].type == OPRT_OR)
			to = idx - 2;
	}
}

void move_redirection_token(std::vector<token> *ptoken_stream)
{
	move_left_redirect(ptoken_stream);
	move_right_redirect(ptoken_stream);
}
