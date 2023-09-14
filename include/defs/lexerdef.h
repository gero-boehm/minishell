#ifndef LEXERDEF_H
# define LEXERDEF_H

# include <stddef.h>
# include "arraydef.h"

typedef enum e_quote
{
	QUOTE_SINGLE = '\'',
	QUOTE_DOUBLE = '"',
	QUOTE_NONE = 0,
}	t_quote;

typedef enum e_token_type
{
	TOKEN_TYPE_OPERAND,
	TOKEN_TYPE_REDIRECTION,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_PARENTHESIS,
}	t_token_type;

typedef enum e_token_subtype
{
	TOKEN_SUBTYPE_AND,
	TOKEN_SUBTYPE_OR,
	TOKEN_SUBTYPE_PIPE,
	TOKEN_SUBTYPE_IN,
	TOKEN_SUBTYPE_HEREDOC,
	TOKEN_SUBTYPE_OUT,
	TOKEN_SUBTYPE_OUT_APPEND,
	TOKEN_SUBTYPE_OPENING,
	TOKEN_SUBTYPE_CLOSING,
	TOKEN_SUBTYPE_NONE,
}	t_token_subtype;

typedef struct s_fragment
{
	char	*str;
	size_t	length;
	t_quote	quote;
}	t_fragment;

typedef struct s_quote_index
{
	t_quote			quote;
	unsigned long	index;
	size_t			count;
}	t_quote_index;

typedef struct s_token
{
	char			*str;
	size_t			length;
	t_array			vars;
	t_token_type	type;
	t_token_subtype	subtype;
	int				contained_quotes;
}	t_token;

#endif