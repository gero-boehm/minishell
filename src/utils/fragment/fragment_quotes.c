#include "fragment.h"
#include "array.h"
#include "str.h"

int	fragment_is_quote_matching(char *fragment, t_quote quote)
{
	if (quote == QUOTE_ANY)
		return (*fragment == QUOTE_SINGLE || *fragment == QUOTE_DOUBLE);
	else
		return (*fragment == quote);
}

size_t	fragment_quote_count(t_array *fragments, unsigned long index, t_quote quote, int ignore_escape)
{
	char			*fragment;
	unsigned long	escaped;

	fragment = *(char **) arr_get(fragments, index);
	if (!fragment_is_quote_matching(fragment, quote))
		return (0);
	if (ignore_escape)
		escaped = 0;
	else
		escaped = fragment_is_escaped(fragments, index);
	return (str_len(fragment) - escaped);
}


