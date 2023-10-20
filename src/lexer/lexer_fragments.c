#include "lexer.h"
#include "array.h"
#include "str.h"

static int	lexer_fragment_add(char *str, t_array *fragments)
{
	t_fragment	fragment;

	fragment.str = str;
	fragment.length = str_len(str);
	fragment.quote = QUOTE_NONE;
	return (arr_add(fragments, &fragment));
}

static int	lexer_fragments_from_boundaries(
		char *str, t_array *boundaries, t_array *fragments)
{
	unsigned long	i;
	unsigned long	end;
	t_range			range;
	char			*fragment_str;

	if (arr_size(boundaries) == 0)
		return (lexer_fragment_add(str, fragments));
	i = 0;
	range.start = 0;
	while (i < arr_size(boundaries))
	{
		end = *(unsigned long *) arr_get(boundaries, i);
		range.length = end - range.start;
		if (range.length == 0)
		{
			i++;
			continue ;
		}
		if (str_extract_range(str, &range, &fragment_str))
			return (2);
		if (lexer_fragment_add(fragment_str, fragments))
			return (3);
		range.start = end;
		i++;
	}
	return (0);
}

int	lexer_fragments_get(char *str, t_array *fragments)
{
	t_array	boundaries;

	if (arr_create(fragments, sizeof(t_fragment)))
		return (1);
	if (lexer_boundaries_get(str, &boundaries))
		return (2);
	if (lexer_fragments_from_boundaries(str, &boundaries, fragments))
		return (3);
	arr_free(&boundaries);
	return (0);
}
