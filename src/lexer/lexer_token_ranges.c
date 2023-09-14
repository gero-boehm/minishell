#include "array.h"
#include "range.h"

static int	lexer_token_range_start(t_array *mask, unsigned long *start, int *mask_value)
{
	while (*start < arr_size(mask))
	{
		*mask_value = *(int *) arr_get(mask, *start);
		if (*mask_value != 0)
			return (0);
		(*start)++;
	}
	return (1);
}

static unsigned long	lexer_token_range_end(t_array *mask, unsigned long index, int match)
{
	int	mask_value;

	while (index < arr_size(mask))
	{
		mask_value = *(int *) arr_get(mask, index);
		if (mask_value != match)
			return (index);
		index++;
	}
	return (index);
}

static int	lexer_token_range_add(unsigned long start, unsigned long end, t_array *token_ranges)
{
	t_range	token_range;

	token_range.start = start;
	token_range.length = end - start;
	return (arr_add(token_ranges, &token_range));
}

int	lexer_token_ranges_get(t_array *mask, t_array *token_ranges)
{
	unsigned long	start;
	unsigned long	end;
	int				mask_value;

	if (arr_create(token_ranges, sizeof(t_range)))
		return (1);
	start = 0;
	while (1)
	{
		if (lexer_token_range_start(mask, &start, &mask_value))
			return (0);
		end = lexer_token_range_end(mask, start, mask_value);
		if (lexer_token_range_add(start, end, token_ranges))
			return (2);
		start = end;
	}
	return (0);
}