#include "array.h"
#include "range.h"

static unsigned long	lexer_token_range_end(t_array *array, unsigned long i)
{
	int	value;

	while (i < arr_size(array))
	{
		value = *(int *) arr_get(array, i);
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

static unsigned long	lexer_get_start(t_array *array)
{
	unsigned long	value;

	value = *(int *) arr_get(array, 0);
	return (value == 0);
}

int	lexer_token_ranges_get(t_array *array, t_array *token_ranges)
{
	unsigned long	start;
	unsigned long	end;

	if (arr_create(token_ranges, sizeof(t_range)))
		return (1);
	start = lexer_get_start(array);
	while (start < arr_size(array))
	{
		end = lexer_token_range_end(array, start);
		if (lexer_token_range_add(start, end, token_ranges))
			return (2);
		start = end + 1;
	}
	return (0);
}