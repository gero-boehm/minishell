#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "str.h"

int	converter_convert_builtin_cd(t_raw_command *raw_command, t_builtin_cd *data)
{
	t_range	range;

	if (arr_size(&raw_command->args) == 1)
		return (str_dup("~", &data->path));
	range.start = 1;
	range.length = 1;
	return (str_from_arr_range(&raw_command->args, &range, "", &data->path));
}
