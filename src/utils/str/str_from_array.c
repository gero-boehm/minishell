#include "str.h"
#include "array.h"
#include "memory.h"

static size_t	get_combined_len_of_elements(t_array *arr, t_range *range)
{
	unsigned long	i;
	size_t			len;
	char			*tmp;

	i = 0;
	len = 0;
	while (i < range->length)
	{
		tmp = *(char **) arr_get(arr, range->start + i);
		len += str_len(tmp);
		i++;
	}
	return (len);
}

static void	copy_elements_into_str(t_array *arr, t_range *range, char *str)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < range->length)
	{
		tmp = *(char **) arr_get(arr, range->start + i);
		str += str_cpyn(str, tmp);
		i++;
	}
}

int	str_from_arr_range(t_array *arr, t_range *range, char **str)
{
	size_t	len;

	len = get_combined_len_of_elements(arr, range);
	if (mem_alloc_str(len, str))
		return (1);
	copy_elements_into_str(arr, range, *str);
	return (0);
}

int	str_from_arr(t_array *arr, char **str)
{
	t_range	range;

	range.start = 0;
	range.length = arr_size(arr);
	return (str_from_arr_range(arr, &range, str));
}
