#include "cmddef.h"
#include "array.h"
#include "range.h"
#include "str.h"
#include "path.h"

static int	is_newline_flag(char *str)
{
	if(*str != '-')
		return (0);
	str++;
	while (*str != '\0')
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

static void get_newline_flag(t_array *args, t_builtin_echo *data, unsigned long *index)
{
	char	*arg;

	data->newline = 1;
	while (*index < arr_size(args))
	{
		arg = *(char **) arr_get(args, *index);
		if (!is_newline_flag(arg))
			return ;
		data->newline = 0;
		(*index)++;
	}
}

static int	converter_expand_paths(t_array *args, t_range *range)
{
	unsigned long	i;
	char			**arg;

	i = range_start(range);
	while (i < range_end(range))
	{
		arg = (char **) arr_get(args, i);
		if (path_expand(arg))
			return (1);
		i++;
	}
	return (0);
}

int	converter_convert_builtin_echo(t_raw_command *raw_command, t_builtin_echo *data)
{
	t_range	range;

	range.start = 1;
	get_newline_flag(&raw_command->args, data, &range.start);
	range.length = arr_size(&raw_command->args) - range.start;
	if (converter_expand_paths(&raw_command->args, &range))
		return (1);
	return (str_from_arr_range(&raw_command->args, &range, " ", &data->str));
}