
#include "lexer.h"
#include <cstring>

static void skip_whitespace(lexer *plexer)
{
	while (plexer->cur_ptr < plexer->input_size && isspace(plexer->input[plexer->cur_ptr]))
		plexer->cur_ptr++;
	plexer->next_ptr = plexer->cur_ptr + 1;
}

//
static token get_next_token(lexer *plexer)
{
	token t;

	skip_whitespace(plexer);
	t.type = get_token_type(plexer);
	if (LPAR <= t.type && t.type <= WCARD) // single char
	{
		t.field.push_back(plexer->input[plexer->cur_ptr]);
		plexer->cur_ptr++;
		plexer->next_ptr++;
	}
	else if (OPRT_AND <= t.type && t.type <= RDICT_APPEND) // double char
	{
		t.field.push_back(plexer->input[plexer->cur_ptr]);
		t.field.push_back(plexer->input[plexer->next_ptr]);
		plexer->cur_ptr += 2;
		plexer->next_ptr += 2;
	}
	else if (KEY_ECHO <= t.type && t.type <= KEY_EXIT) // key word
		get_keyword(plexer, &t);
	else if (t.type == IDENT)
		get_ident(plexer, &t);
	else
		plexer->cur_ptr++;
	plexer->next_ptr = plexer->cur_ptr + 1;
	return t;
}

//
std::vector<token> tokenize(const char *cstr)
{
	std::vector<token> token_stream;
	lexer *plexer;

	plexer = new lexer;
	plexer->input = cstr;
	plexer->input_size = strlen(cstr);
	plexer->cur_ptr = 0;
	plexer->next_ptr = 1;
	while (plexer->cur_ptr < plexer->input_size)
		token_stream.push_back(get_next_token(plexer));
	delete (plexer);
	return token_stream;
}
