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

#endif