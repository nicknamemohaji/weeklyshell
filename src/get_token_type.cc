
#include "lexer.h"
#include <cstring>

static int get_token_type2(lexer *plexer, const char *pc)
{
	if (*pc == '&' && *(pc + 1) == '&')
		return (OPRT_AND);
	else if (strncmp(pc, "echo", 4) == 0 && isspace(*(pc + 4)))
		return (KEY_ECHO);
	else if (strncmp(pc, "env", 3) == 0 && isspace(*(pc + 3)))
		return (KEY_ENV);
	else if (strncmp(pc, "unset", 5) == 0 && isspace(*(pc + 5)))
		return (KEY_UNSET);
	else if (strncmp(pc, "exit", 4) == 0 && isspace(*(pc + 4)))
		return (KEY_EXIT);
	else if (strncmp(pc, "export", 6) == 0 && isspace(*(pc + 6)))
		return (KEY_EXPORT);
	else if (strncmp(pc, "cd", 2) == 0 && isspace(*(pc + 2)))
		return (KEY_CD);
	else if (strncmp(pc, "pwd", 3) == 0 && isspace(*(pc + 3)))
		return (KEY_PWD);
	else if (is_letter(*pc))
		return (IDENT);
	return (ILLEGAL);
}

int get_token_type(lexer *plexer)
{
	const char *pc = plexer->input + plexer->cur_ptr;

	if (*pc == '(')
		return (LPAR);
	else if (*pc == ')')
		return (RPAR);
	else if (*pc == '|')
	{
		if (*(pc + 1) == '|')
			return (OPRT_OR);
		return (PIPE);
	}
	else if (*pc == '<')
	{
		if (*(pc + 1) == '<')
			return (RDICT_HEREDOC);
		return (RDICT_READ);
	}
	else if (*pc == '>')
	{
		if (*(pc + 1) == '>')
			return (RDICT_APPEND);
		return (RDICT_WRITE);
	}
	return (get_token_type2(plexer, pc));
}
