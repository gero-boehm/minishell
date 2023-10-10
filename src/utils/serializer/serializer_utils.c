#include "array.h"
#include "str.h"

int	append_str(const char *str, t_array *lines)
{
	char *dup;

	if (str_dup(str, &dup))
		return (1);
	if (arr_add(lines, &dup))
		return (2);
	return (0);
}
