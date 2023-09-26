#include "cmddef.h"
#include "array.h"
#include "str.h"

int converter_convert_external(t_raw_command *raw_command, t_external *data)
{
	return (str_arr_from_arr(&raw_command->args, &data->args));
}
