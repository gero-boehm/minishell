#include "array.h"
#include "range.h"
#include "str.h"
#include "vars.h"

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
		if (vars_extract(fragment->str, 0, length, vars))
			return (2);
		length += fragment->length;
		i++;
	}
	return (0);
}
