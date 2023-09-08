#include "lexerdef.h"
#include "array.h"
#include "str.h"

static int	lexer_quote_index_single(t_array *fragments, unsigned long index, t_array *indices)
{
	t_quote_index	quote_index;
	char			*fragment;

	fragment = *(char **) arr_get(fragments, index);
	if (*fragment != '\'')
		return (0);
	quote_index.quote = QUOTE_SINGLE;
	quote_index.index = index;
	quote_index.count = str_len(fragment);
	return (arr_add(indices, &quote_index));
}

static int	lexer_quote_index_double(t_array *fragments, unsigned long index, t_array *indices)
{
	t_quote_index	quote_index;
	char			*fragment;

	fragment = *(char **) arr_get(fragments, index);
	if (*fragment != '"')
		return (0);
	quote_index.quote = QUOTE_DOUBLE;
	quote_index.index = index;
	quote_index.count = str_len(fragment);
	return (arr_add(indices, &quote_index));
}

int	lexer_quotes_indices(t_array *fragments, t_array *indices)
{
	unsigned long	i;
	char			*fragment;

	if (arr_create(indices, sizeof(t_quote_index)))
		return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		if (lexer_quote_index_single(fragments, i, indices))
			return (2);
		if (lexer_quote_index_double(fragments, i, indices))
			return (3);
		i++;
	}
	return (0);
}
