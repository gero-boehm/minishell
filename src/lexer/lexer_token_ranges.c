#include "skipdef.h"
#include "array.h"
#include "range.h"

static int	lexer_is_space_in_quotes(t_array *quote_ranges, unsigned long index)
{
	unsigned long	i;
	t_range			*quote_range;

	i = 0;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_range *) arr_get(quote_ranges, i);
		if (range_contains(quote_range, index))
			return (1);
		i++;
	}
	return (0);
}

static unsigned long	lexer_token_range_end(t_array *spaces, t_array *quote_ranges, unsigned long *index)
{
	unsigned long	space;

	while (++(*index) < arr_size(spaces))
	{
		space = *(unsigned long *) arr_get(spaces, *index);
		if (lexer_is_space_in_quotes(quote_ranges, space))
			continue ;
		return (space);
	}
	return (0);
}

static int	lexer_quote_ranges_get_contained(t_array *quote_ranges, t_range *token_range)
{
	unsigned long	i;
	t_range			*quote_range;

	if (arr_create(&token_range->meta.token_data.quote_ranges, sizeof(t_range)))
		return (1);
	i = 0;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_range *) arr_get(quote_ranges, i);
		if (!range_contains_range(token_range, quote_range))
			SKIP(i);
		if (arr_add(&token_range->meta.token_data.quote_ranges, quote_range))
			return (2);
		i++;
	}
	return (0);
}

static int	lexer_token_range_add(t_array *quote_ranges, t_array *token_ranges, unsigned long start, unsigned long end)
{
	t_range	token_range;

	token_range.start = start;
	token_range.length = end - start;
	if (lexer_quote_ranges_get_contained(quote_ranges, &token_range))
		return (1);
	return (arr_add(token_ranges, &token_range));
}

int	lexer_token_ranges_get(t_array *array, t_array *token_ranges)
{
	unsigned long	i;
	unsigned long	start;
	unsigned long	end;

	if (arr_create(token_ranges, sizeof(t_range)))
		return (1);
	i = 0;
	while (i < arr_size(spaces) - 1)
	{
		start = *(unsigned long *) arr_get(spaces, i);
		if (i > 0)
			start++;
		end = lexer_token_range_end(spaces, quote_ranges, &i);
		if (lexer_token_range_add(quote_ranges, token_ranges, start, end))
			return (2);
	}
	return (0);
}