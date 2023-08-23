#include "fragment.h"
#include "array.h"

static int	is_unclosed(unsigned long count)
{
	return (count % 2);
}

int	lexer_quotes_unclosed(t_array *fragments)
{
	unsigned long	i;
	unsigned long	quotes_single;
	unsigned long	quotes_double;

	i = 0;
	quotes_single = 0;
	quotes_double = 0;
	while (i < arr_size(fragments))
	{
		quotes_single += fragment_quote_count(fragments, i, QUOTE_SINGLE, 0);
		quotes_double += fragment_quote_count(fragments, i, QUOTE_DOUBLE, 0);
		i++;
	}
	return (is_unclosed(quotes_single) || is_unclosed(quotes_double));
}
