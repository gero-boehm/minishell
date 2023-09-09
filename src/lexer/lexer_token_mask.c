#include "array.h"
#include "range.h"
#include "str.h"

static int lexer_mask_value_get(t_fragment *fragment)
{
	if (!str_char_is_whitespace(*fragment->str))
		return (1);
	return (fragment->quote != QUOTE_NONE);
}

int	lexer_token_mask_get(t_array *fragments, t_array *mask)
{
	unsigned long	i;
	t_fragment		*fragment;
	int				value;

	if (arr_create(mask, sizeof(int)))
		return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		value = lexer_mask_value_get(fragment);
		if (arr_add(mask, &value))
			return (2);
		i++;
	}
	return (0);
}