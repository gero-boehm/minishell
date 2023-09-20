#ifndef TOKENDEF_H
# define TOKENDEF_H

# include "arraydef.h"

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