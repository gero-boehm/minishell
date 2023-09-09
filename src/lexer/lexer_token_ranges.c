#include "array.h"
#include "range.h"

static unsigned long	lexer_token_range_end(t_array *mask, unsigned long i)
{
	int	value;

	while (i < arr_size(mask))
	{
		value = *(int *) arr_get(mask, i);
		if (value == 0)
			return (i);
		i++;
	}
	return (i);
}

static int	lexer_token_range_add(unsigned long start, unsigned long end, t_array *token_ranges)
{
	t_range	token_range;

	token_range.start = start;
	token_range.length = end - start;
	return (arr_add(token_ranges, &token_range));
}

static unsigned long	lexer_get_start(t_array *mask)
{
	unsigned long	value;

	value = *(int *) arr_get(mask, 0);
	return (value == 0);
}

int	lexer_token_ranges_get(t_array *mask, t_array *token_ranges)
{
	unsigned long	start;
	unsigned long	end;

	if (arr_create(token_ranges, sizeof(t_range)))
		return (1);
	start = lexer_get_start(mask);
	while (start < arr_size(mask))
	{
		end = lexer_token_range_end(mask, start);
		if (lexer_token_range_add(start, end, token_ranges))
			return (2);
		start = end + 1;
	}
	return (0);
}