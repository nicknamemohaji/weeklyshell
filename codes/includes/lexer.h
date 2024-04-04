/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogwak <dogwak@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:08:08 by dogwak            #+#    #+#             */
/*   Updated: 2024/03/26 18:08:5 by dogwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_string.h"
# include "ft_vector.h"

enum			e_token_type
{
	ILLEGAL,
	LPAR,
	RPAR,
	PIPE,
	RDICT_READ,
	RDICT_WRITE,
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
	IDENT,
	FILE_NAME,
	END
};

// struct of token object
// need string as a field.
typedef struct s_token
{
	int			type;
	t_ft_string	field;
}				t_token;

// constructor and destructor of the token object
t_token			construct_token(int token_type);
void			destruct_token(t_token *this);

typedef struct s_lexer
{
	const char	*input;
	int			input_size;
	int			cur_ptr;
	int			next_ptr;
}				t_lexer;

// if the 'c' is a meta character, return false
int				is_letter(const char c);

int				get_token_type(t_lexer *plexer);
int				get_ident(t_lexer *plexer, t_token *ptoken);
int				get_quoted_ident(t_lexer *plexer, t_token *ptoken);
int				get_keyword(t_lexer *plexer, t_token *ptoken);

// tokenize the input string.
// return vector of token.
// return NULL if error occured.
t_ft_vector		*tokenize(const char *cstr);

// move redirection operator and file name to proper position.
// without this, operator cannot find proper operand.
void			move_redirection_token(t_ft_vector *ptoken_stream);

#endif
