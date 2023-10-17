#include "cmddef.h"
#include "array.h"
#include "str.h"

static int	extract_key_value_pair(char *arg, t_array *keys, t_array *values)
{
	char	*key;
	char	*value;

	if (str_key_value(arg, &key, &value))
		return (1);
	if (arr_add(keys, &key))
		return (2);
	if (arr_add(values, &value))
		return (3);
	return (0);
}

int	converter_convert_builtin_export(
		t_raw_command *raw_command, t_builtin_export *data)
{
	unsigned long	i;
	t_array			keys;
	t_array			values;
	char			*arg;

	if (arr_create(&keys, sizeof(char *)))
		return (1);
	if (arr_create(&values, sizeof(char *)))
		return (2);
	i = 1;
	while (i < arr_size(&raw_command->args))
	{
		arg = *(char **) arr_get(&raw_command->args, i);
		if (extract_key_value_pair(arg, &keys, &values))
			return (3);
		i++;
	}
	if (str_arr_from_arr(&keys, &data->keys))
		return (4);
	if (str_arr_from_arr(&values, &data->values))
		return (5);
	arr_free_ptr(&keys);
	arr_free_ptr(&values);
	return (0);
}
