#include "lexer.h"
#include "fragment.h"
#include "array.h"
#include "error.h"

static int	lexer_get_next_quote(t_array *fragments, unsigned long start, t_quote *quote, unsigned long *index)
{
	unsigned long	i;
	char			*fragment;

	i = start;
	while (i < arr_size(fragments))
	{
		if (fragment_quote_count(fragments, i, QUOTE_ANY, *quote == QUOTE_SINGLE) % 2 == 0)
		{
			i++;
			continue ;
		}
		fragment = *(char **) arr_get(fragments, i);
		if (!fragment_is_quote_matching(fragment, *quote))
		{
			i++;
			continue ;
		}
		*quote = *fragment;
		*index = i;
		return (0);
	}
	return (1);
}

char	*lexer_get_invalid_token(t_quote quote)
{
	if (quote == QUOTE_SINGLE)
		return ("'");
	if (quote == QUOTE_DOUBLE)
		return ("\"");
	return ("");
}

static int	lexer_get_range_of_quotes(t_array *fragments, unsigned long start, t_quote_range *quote_range)
{
	unsigned long	index;

	quote_range->quote = QUOTE_ANY;
	if (lexer_get_next_quote(fragments, start, &quote_range->quote, &index))
		return (1);
	quote_range->range.start = index;
	start = index + 1;
	if (lexer_get_next_quote(fragments, start, &quote_range->quote, &index))
		error_syntax(lexer_get_invalid_token(quote_range->quote));
	quote_range->range.length = index - start + 1;
	return (0);
}

int	lexer_get_ranges_of_quotes(t_array *fragments, t_array *quote_ranges)
{
	t_quote_range	quote_range;
	unsigned long	start;

	if (arr_create(quote_ranges, sizeof(t_quote_range)))
		return (1);
	start = 0;
	while (1)
	{
		if (lexer_get_range_of_quotes(fragments, start, &quote_range))
			return (0);
		if (arr_add(quote_ranges, &quote_range))
			return (2);
		start = quote_range.range.start + quote_range.range.length + 1;
	}
	return (3);
}
