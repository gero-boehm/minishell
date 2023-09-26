#include "skipdef.h"
#include "array.h"
#include "range.h"
#include "str.h"

static const char *boundaries = " !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";

static void	lexer_var_range_get(t_fragment *fragment, t_range *var_range)
{
	char	c;

	var_range->start += var_range->length - 1;
	var_range->length = 1;
	while (1)
	{
		c = fragment->str[range_end(var_range)];
		if (c == '?')
		{
			var_range->length++;
			return ;
		}
		if (c == '\0' || str_char_in_set(boundaries, c))
			return ;
		var_range->length++;
	}
}

static int	lexer_key_extract(t_fragment *fragment, t_range *var_range)
{
	t_range	key_range;

	key_range.start = var_range->start + 1;
	key_range.length = var_range->length - 1;
	return (str_extract_range(fragment->str, &key_range, &var_range->meta.var_data.key));
}

static int	lexer_vars_extract(t_fragment *fragment, size_t offset, t_range *vars)
{
	unsigned long	start;
	t_range			var_range;

	start = 0;
	while (1)
	{
		if (str_range_of(fragment->str, "$", start, &var_range))
			return (0);
		lexer_var_range_get(fragment, &var_range);
		if (range_length(&var_range) == 1)
		{
			start = range_end(&var_range);
			continue ;
		}
		if (lexer_key_extract(fragment, &var_range))
			return (1);
		var_range.start += offset;
		if (arr_add(vars, &var_range))
			return (2);
		start = range_end(&var_range);
	}
	return (3);
}

int	lexer_vars_get(t_array *fragments, t_array *vars)
{
	unsigned long	i;
	t_fragment		*fragment;
	size_t			length;

	if (arr_create(vars, sizeof(t_range)))
		return (1);
	i = 0;
	length = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		if (fragment->quote == QUOTE_SINGLE)
		{
			length += fragment->length;
			i++;
			continue ;
		}
		if (lexer_vars_extract(fragment, length, vars))
			return (2);
		length += fragment->length;
		i++;
	}
	return (0);
}
