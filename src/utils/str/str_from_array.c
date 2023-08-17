#include "str.h"
#include "array.h"
#include "memory.h"

static size_t	get_total_str_len(t_array *arr)
{
	unsigned long	i;
	size_t			len;
	char			*tmp;

	i = 0;
	len = 0;
	while (i < arr_size(arr))
	{
		tmp = *(char **) arr_get(arr, i);
		len += str_len(tmp);
		i++;
	}
	return (len);
}

static void	copy_elements_into_str(t_array *arr, char *str)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < arr_size(arr))
	{
		tmp = *(char **) arr_get(arr, i);
		str += str_cpyn(str, tmp);
		i++;
	}
}

int	str_from_arr(t_array *arr, char **str)
{
	size_t			len;

	len = get_total_str_len(arr);
	if (mem_alloc_str(len, str))
		return (1);
	copy_elements_into_str(arr, *str);
	return (0);
}
