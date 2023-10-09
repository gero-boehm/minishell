#include <stdio.h>
#include "array.h"
#include "memory.h"

int	arr_remove_at(t_array *arr, unsigned long index)
{
	void	*dst;
	void	*src;
	size_t	len;

	dst = arr_get(arr, index);
	src = arr_get(arr, index + 1);
	len = (arr->size - index - 1) * arr->bytes;
	mem_ncpy(dst, src, len);
	arr->size--;
	return (0);
}

int	arr_remove(t_array *arr, void *element)
{
	unsigned long	index;

	if (arr_index(arr, element, &index))
		return (0);
	if (arr_remove_at(arr, index))
		return (1);
	return (0);
}
