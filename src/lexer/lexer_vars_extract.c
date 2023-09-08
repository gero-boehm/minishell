#include <stdio.h>
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

static int	lexer_var_get(t_array *fragments, unsigned long index, t_range *token_range)
{
	unsigned long	start;
	char			*fragment;
	t_range			var_range;
	t_range			key_range;

	start = 0;
	while (1)
	{
		fragment = *(char **) arr_get(fragments, index);
		if (str_range_of(fragment, "$", start, &var_range))
			return (0);
		var_range.start += var_range.length - 1;
		lexer_var_get_range(fragment, &var_range);
		var_range.meta.var_data.index = index;
		key_range.start = var_range.start + 1;
		key_range.length = var_range.length - 1;
		if (str_extract_range(fragment, &key_range, &var_range.meta.var_data.key))
			return (1);
		if (arr_add(&token_range->meta.token_data.var_ranges, &var_range))
			return (2);
		start = range_end(&var_range);
	}
	return (2);
}

static int	lexer_index_in_single_quotes(t_range *token_range, unsigned long index)
{
	unsigned long	i;
	t_array			*quote_ranges;
	t_range			*quote_range;

	i = 0;
	quote_ranges = &token_range->meta.token_data.quote_ranges;
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

static int lexer_create_var_ranges(t_range *token_range)
{
	t_array	*var_ranges;

	var_ranges = &token_range->meta.token_data.var_ranges;
	return (arr_create(var_ranges, sizeof(t_range)));
}

static int	lexer_vars_get(t_array *fragments, t_range *token_range)
{
	unsigned long	i;

	if (lexer_create_var_ranges(token_range))
		return (1);
	i = range_start(token_range);
	while (i < range_end(token_range))
	{
		if (lexer_index_in_single_quotes(token_range, i))
			SKIP(i);
		if (lexer_var_get(fragments, i, token_range))
			return (1);
		i++;
	}
	return (0);
}

int	lexer_vars_extract(t_array *fragments, t_array *token_ranges)
{
	unsigned long	i;
	t_range			*token_range;

	i = 0;
	while (i < arr_size(token_ranges))
	{
		token_range = (t_range *) arr_get(token_ranges, i);
		if (lexer_vars_get(fragments, token_range))
			return (2);
		i++;
	}
	return (0);
}