#include "array.h"
#include "range.h"

int	arr_sub(t_array *arr, t_range *range, t_array *sub)
{
	unsigned long	i;
	void			*tmp;

	if (arr_create(sub, arr->bytes))
		return (1);
	i = range_start(range);
	while (i < range_end(range))
	{
		tmp = arr_get(arr, i);
		if (arr_add(sub, tmp))
			return (2);
		i++;
	}
	return (0);
}

int	arr_sub_mask(t_array *arr, t_array *mask, t_array *sub)
{
	unsigned long	i;
	int				mask_value;
	void			*tmp;

	if (arr_create(sub, arr->bytes))
		return (1);
	i = 0;
	while (i < arr_size(arr))
	{
		mask_value = *(int *) arr_get(mask, i);
		if (mask_value == 0)
		{
			i++;
			continue ;
		}
		tmp = arr_get(arr, i);
		if (arr_add(sub, tmp))
			return (2);
		i++;
	}
	return (0);
}
