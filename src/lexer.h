
#include <vector>
#include <string>

// enumerator for token type
enum token_type
{
	ILLEGAL,
	LPAR,
	RPAR,
	PIPE,
	RDICT_READ,
	RDICT_WRITE,
	WCARD,
	OPRT_AND,
	OPRT_OR,
	RDICT_HEREDOC,
	RDICT_APPEND,
	KEY_ECHO,
	KEY_CD,
	KEY_PWD,
	KEY_EXPORT,
	KEY_UNSET,
	KEY_ENV,
	KEY_EXIT,
	IDENT
};

// struct for token
typedef struct token
{
	int type;
	std::string field;
} token;

typedef struct lexer
{
	const char *input;
	int input_size;
	int cur_ptr;
	int next_ptr;
} lexer;

int is_letter(const char c);

int get_token_type(lexer *plexer);
int get_ident(lexer *plexer, token *ptoken);
int get_quoted_ident(lexer *plexer, token *ptoken);
int get_keyword(lexer *plexer, token *ptoken);

std::vector<token> tokenize(const char *cstr);
