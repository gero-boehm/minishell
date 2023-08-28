#include "lexerdef.h"
#include "fragment.h"
#include "array.h"
#include "str.h"

static int	lexer_is_string_boundary(t_array *fragments, unsigned long index, t_quote quote)
{
	const char	*set = " \n\t\r\f\v&()<>|";
	char		*fragment;

	fragment = *(char **) arr_get(fragments, index);
	if (str_char_in_set(set, *fragment))
		return (1);
	return (fragment_quote_count(fragments, index, QUOTE_ANY, quote == QUOTE_SINGLE) > 0);
}

void	lexer_expand_quote_range_boundary(t_array *fragments, unsigned long *boundary, t_quote quote, int direction)
{
	while (1)
	{
		if (*boundary == 0 || *boundary == arr_size(fragments) - 1)
			return ;
		if (lexer_is_string_boundary(fragments, *boundary + direction, quote))
			return ;
		*boundary += direction;
	}
}

void	lexer_expand_quote_range_boundaries(t_array *fragments, t_quote_range *quote_range)
{
	unsigned long	boundary_end;

	boundary_end = quote_range->range.start + quote_range->range.length;
	lexer_expand_quote_range_boundary(fragments, &quote_range->range.start, quote_range->quote, -1);
	lexer_expand_quote_range_boundary(fragments, &boundary_end, quote_range->quote, 1);
	quote_range->range.length = boundary_end - quote_range->range.start;
}

void	lexer_expand_quote_ranges(t_array *fragments, t_array *quote_ranges)
{
	unsigned long	i;
	t_quote_range	*quote_range;

	i = 0;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_quote_range *) arr_get(quote_ranges, i);
		lexer_expand_quote_range_boundaries(fragments, quote_range);
		i++;
	}
}
