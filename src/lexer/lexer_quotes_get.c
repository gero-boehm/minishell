#include "array.h"
#include "range.h"
#include "error.h"

static int lexer_quote_is_closing(t_quote_index *quote_index, t_quote quote)
{
	if (quote_index->quote != quote)
		return (0);
	return (quote_index->count % 2);
}

static int	lexer_quote_closing_get(t_array *indices, t_quote quote, unsigned long *index, t_quote_index **end)
{
	while (++(*index) < arr_size(indices))
	{
		*end = (t_quote_index *) arr_get(indices, *index);
		if (lexer_quote_is_closing(*end, quote))
			return (0);
	}
	return (1);
}

static char	*lexer_quote_str(t_quote quote)
{
	if (quote == QUOTE_SINGLE)
		return ("'");
	if (quote == QUOTE_DOUBLE)
		return ("\"");
	return ("");
}

static int	lexer_quote_range_add(t_array *ranges, t_quote_index *start, t_quote_index *end)
{
	t_range	range;

	range.meta.quote = start->quote;
	range.start = start->index;
	range.length = end->index - start->index + 1;
	return (arr_add(ranges, &range));
}

int	lexer_quotes_get(t_array *indices, t_array *ranges)
{
	unsigned long	i;
	t_quote_index	*quote_start;
	t_quote_index	*quote_end;

	if (arr_create(ranges, sizeof(t_range)))
		return (1);
	i = 0;
	while (i < arr_size(indices))
	{
		quote_start = (t_quote_index *) arr_get(indices, i);
		if (lexer_quote_closing_get(indices, quote_start->quote, &i, &quote_end))
			error_syntax(lexer_quote_str(quote_start->quote));
		if (lexer_quote_range_add(ranges, quote_start, quote_end))
			return (24);
		i++;
	}
	return (0);
}