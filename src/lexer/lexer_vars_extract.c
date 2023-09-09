#include "skipdef.h"
#include "array.h"
#include "range.h"
#include "str.h"

static const char *boundaries = " !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";

static void	lexer_var_get_range(char *fragment, t_range *var_range)
{
	char	c;

	while (1)
	{
		c = fragment[range_end(var_range)];
		if (c == '\0' || str_char_in_set(boundaries, c))
			return ;
		var_range->length++;
	}
}

static int	lexer_vars_extract(char *fragment, unsigned long index, t_range *vars)
{
	unsigned long	start;
	t_range			var_range;
	t_range			key_range;

	start = 0;
	while (1)
	{
		if (str_range_of(fragment, "$", start, &var_range))
			return (0);
		var_range.start += var_range.length - 1;
		var_range.length = 1;
		lexer_var_get_range(fragment, &var_range);
		if (range_length(&var_range) == 1)
		{
			start = range_end(&var_range);
			continue ;
		}
		var_range.meta.var_data.index = index;
		key_range.start = var_range.start + 1;
		key_range.length = var_range.length - 1;
		if (str_extract_range(fragment, &key_range, &var_range.meta.var_data.key))
			return (1);
		if (arr_add(vars, &var_range))
			return (2);
		start = range_end(&var_range);
	}
	return (3);
}

static int	lexer_fragment_ignore(t_array *quote_ranges, unsigned long index)
{
	unsigned long	i;
	t_range			*quote_range;

	i = 0;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_range *) arr_get(quote_ranges, i);
		if (quote_range->meta.quote != QUOTE_SINGLE)
			SKIP(i);
		if (range_contains(quote_range, index))
			return (1);
		i++;
	}
	return (0);
}

int	lexer_vars_get(t_array *fragments, t_array *quote_ranges, t_array *vars)
{
	unsigned long	i;
	char			*fragment;

	if (arr_create(vars, sizeof(t_range)))
		return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		if (lexer_fragment_ignore(quote_ranges, i))
			SKIP(i);
		fragment = *(char **) arr_get(fragments, i);
		if (lexer_vars_extract(fragment, i, vars))
			return (2);
		i++;
	}
	return (0);
}
