#include "deserializer.h"
#include "array.h"
#include "str.h"

int	deserializer_deserialize_args(
		t_array *lines, unsigned long *index, t_array *args)
{
	char	*line;
	char	*arg;

	if (!line_matches(lines, *index, "args"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "arg"))
			break ;
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (str_dup(line, &arg))
			return (1);
		if (arr_add(args, &arg))
			return (2);
		(*index)++;
	}
	return (0);
}
