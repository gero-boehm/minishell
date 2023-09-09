#include "skipdef.h"
#include "lexer.h"
#include "array.h"
#include "str.h"

static int	lexer_get_fragments_from_boundaries(char *str, t_array *boundaries, t_array *fragments)
{
	unsigned long	i;
	unsigned long	end;
	t_range 		range;
	char			*token;

	if (arr_size(boundaries) == 0)
		return (arr_add(fragments, &str));
	i = 0;
	range.start = 0;
	while (i < arr_size(boundaries))
	{
		end = *(unsigned long*) arr_get(boundaries, i);
		range.length = end - range.start;
		if (range.length == 0)
			SKIP(i);
		if (str_extract_range(str, &range, &token))
			return (2);
		if (arr_add(fragments, &token))
			return (3);
		range.start = end;
		i++;
	}
	return (0);
}

int	lexer_get_fragments(char *str, t_array *fragments)
{
	t_array	boundaries;

	if (arr_create(fragments, sizeof(char *)))
		return (1);
	if (lexer_get_boundaries(str, &boundaries))
		return (2);
	if (lexer_get_fragments_from_boundaries(str, &boundaries, fragments))
		return (3);
	arr_free(&boundaries);
	return (0);
}
