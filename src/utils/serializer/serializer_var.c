#include "cmddef.h"
#include "serializer.h"
#include "array.h"
#include "range.h"
#include "number.h"

static int	serializer_serialize_unsigned_long(
		const char *key, unsigned long *value, t_array *lines)
{
	char	*str;

	if (append_str(key, lines))
		return (1);
	if (lutoa(value, &str))
		return (3);
	if (arr_add(lines, &str))
		return (4);
	return (0);
}

static int	serializer_serialize_var(t_range *var, t_array *lines)
{
	if (append_str("var", lines))
		return (1);
	if (serializer_serialize_unsigned_long("start", range_start(var), lines))
		return (2);
	if (serializer_serialize_unsigned_long("length", range_length(var), lines))
		return (3);
	if (serializer_serialize_unsigned_long(
			"index", var->meta.var_data.index, lines))
		return (4);
	if (append_str("key", lines))
		return (1);
	if (arr_add(lines, &var->meta.var_data.key))
		return (6);
	return (0);
}

int	serializer_serialize_vars(
		t_array *vars, const char *vars_name, t_array *lines)
{
	unsigned long	i;
	t_range			*var;

	if (arr_size(vars) == 0)
		return (0);
	if (append_str(vars_name, lines))
		return (1);
	i = 0;
	while (i < arr_size(vars))
	{
		var = (t_range *) arr_get(vars, i);
		if (serializer_serialize_var(var, lines))
			return (2);
		i++;
	}
	return (0);
}
