#include "cmddef.h"
#include "deserializer.h"
#include "array.h"
#include "str.h"

static int	deserializer_deserialize_var_ulong(t_array *lines, unsigned long *index, unsigned long *value)
{
	char	*line;

	(*index)++;
	line = *(char **) arr_get(lines, *index);
	// TODO: replace with proper function for type
	if (str_to_long_unsafe(line, value))
		return (1);
	(*index)++;
	return (0);
}

static int	deserializer_deserialize_var_str(t_array *lines, unsigned long *index, char **value)
{
	char	*line;

	(*index)++;
	line = *(char **) arr_get(lines, *index);
	if (str_dup(line, value))
		return (1);
	(*index)++;
	return (0);
}

static int	deserializer_deserialize_var(t_array *lines, unsigned long *index, t_range *var)
{
	if (line_matches(lines, *index, "start"))
		return (deserializer_deserialize_var_ulong(lines, index, &var->start));
	if (line_matches(lines, *index, "length"))
		return (deserializer_deserialize_var_ulong(lines, index, &var->length));
	if (line_matches(lines, *index, "index"))
		return (deserializer_deserialize_var_ulong(lines, index, &var->meta.var_data.index));
	if (line_matches(lines, *index, "key"))
		return (deserializer_deserialize_var_str(lines, index, &var->meta.var_data.key));
	return (0);
}

int	deserializer_deserialize_vars(t_array *lines, unsigned long *index, const char *vars_name, t_array *vars)
{
	t_range	var;

	if (!line_matches(lines, *index, vars_name))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "var"))
			break ;
		(*index)++;
		if (deserializer_deserialize_var(lines, index, &var))
			return (1);
		if (arr_add(vars, &var))
			return (2);
	}
	return (0);
}
