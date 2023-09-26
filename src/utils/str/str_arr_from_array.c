#include "str.h"
#include "array.h"
#include "memory.h"
#include "range.h"

int	str_arr_from_arr_range(t_array *arr, t_range *range, char ***strs)
{
	unsigned long	i;
	char			*tmp;

	if (mem_alloc_str_arr(range_length(range), strs))
		return (1);
	i = range_start(range);
	while (i < range_end(range))
	{
		tmp = *(char **) arr_get(arr, i);
		if (str_dup(tmp, *strs + i - range_start(range)))
			return (2);
		i++;
	}
	return (0);
}

int	str_arr_from_arr(t_array *arr, char ***strs)
{
	t_range	range;

	range.start = 0;
	range.length = arr_size(arr);
	return (str_arr_from_arr_range(arr, &range, strs));
}
