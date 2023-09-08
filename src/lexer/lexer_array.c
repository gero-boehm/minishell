#include "array.h"
#include "range.h"
#include "str.h"

static int	lexer_space_quoted(char *fragment, unsigned long index, t_array *quote_ranges)
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

int	lexer_get_array(t_array *fragments, t_array *quote_ranges, t_array *array)
{
	unsigned long	i;
	char			*fragment;
	int				keep;

	if (arr_create(array, sizeof(int)))
		return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = *(char **) arr_get(fragments, i);
		keep = 0;
		if (!str_char_is_whitespace(*fragment))
			keep = 1;
		else if (lexer_space_quoted(fragment, i, quote_ranges))
			keep = 1;
		if (arr_add(array, &keep))
			return (2);
		i++;
	}
	return (0);
}