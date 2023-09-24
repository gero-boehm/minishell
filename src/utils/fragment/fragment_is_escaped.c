#include "array.h"
#include "str.h"

int	fragment_is_escaped(t_array *fragments, unsigned long index)
{
	char	*fragment;

	if (index == 0)
		return (0);
	fragment = *(char **) arr_get(fragments, index - 1);
	if (*fragment != '\\')
		return (0);
	return (str_len(fragment) % 2);
}
