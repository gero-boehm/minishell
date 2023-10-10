#include "array.h"
#include "str.h"

int	line_matches(t_array *lines, unsigned long index, const char *match)
{
	char	*line;

	if (index >= arr_size(lines))
		return (0);
	line = *(char **) arr_get(lines, index);
	return (str_eq(line, match));
}
