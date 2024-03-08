
#include "lexer.h"

int is_letter(const char c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '$' || c == '_' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int get_ident(lexer *plexer, token *ptoken)
{
	int flag;

	flag = 0;
	while (plexer->cur_ptr < plexer->input_size)
	{
		if (!flag && (plexer->input[plexer->cur_ptr] == '\'' || plexer->input[plexer->cur_ptr] == '\"'))
			flag = plexer->input[plexer->cur_ptr];
		else if (flag && plexer->input[plexer->cur_ptr] == flag)
			flag = 0;
		else if (!flag && !is_letter(plexer->input[plexer->cur_ptr]))
			break;
		ptoken->field.push_back(plexer->input[plexer->cur_ptr]);
		plexer->cur_ptr++;
	}
	plexer->next_ptr = plexer->cur_ptr + 1;
	return (1);
}

int get_keyword(lexer *plexer, token *ptoken)
{
	if (ptoken->type == KEY_ECHO)
		ptoken->field = "echo";
	else if (ptoken->type == KEY_CD)
		ptoken->field = "cd";
	else if (ptoken->type == KEY_ENV)
		ptoken->field = "env";
	else if (ptoken->type == KEY_EXPORT)
		ptoken->field = "export";
	else if (ptoken->type == KEY_EXIT)
		ptoken->field = "exit";
	else if (ptoken->type == KEY_PWD)
		ptoken->field = "pwd";
	else if (ptoken->type == KEY_UNSET)
		ptoken->field = "unset";
	plexer->cur_ptr += ptoken->field.size();
	plexer->next_ptr = plexer->cur_ptr + 1;
	return (1);
}
