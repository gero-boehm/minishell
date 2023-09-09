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

// typedef enum e_token_type
// {
// 	TOKEN_OPERAND
// }	t_token_type;

// typedef enum e_token_subtype
// {
// 	TOKEN_
// }	t_token_subtype;

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
	char	*str;
	size_t	length;
	t_array	vars;
}	t_token;

#endif