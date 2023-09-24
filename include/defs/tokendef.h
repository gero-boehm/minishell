#ifndef TOKENDEF_H
# define TOKENDEF_H

# include "arraydef.h"

typedef enum e_token_type
{
	TOKEN_INVALID		= 0,
	TOKEN_OPERATOR		= 1,
	TOKEN_REDIRECTION	= 2,
	TOKEN_PARENTHESIS	= 4,
	TOKEN_STRING		= 8,
	TOKEN_AND			= 16,
	TOKEN_OR			= 32,
	TOKEN_PIPE			= 64,
	TOKEN_IN			= 128,
	TOKEN_OUT			= 256,
	TOKEN_HEREDOC		= 512,
	TOKEN_APPEND		= 1024,
	TOKEN_OPENING		= 2048,
	TOKEN_CLOSING		= 4096,
}	t_token_type;

typedef struct s_token
{
	char			*str;
	size_t			length;
	t_array			vars;
	t_token_type	type;
	int				contained_quotes;
}	t_token;

#endif