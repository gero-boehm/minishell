#include <stdlib.h>
#include "global.h"
#include "array.h"
#include "memory.h"

static int	arr_grow(t_array *arr)
{
	void			*new;
	unsigned long	index;

	arr->max_size *= 2;
	if (arr_index(&global()->allocs, &arr->elements, &index))
		return (1);
	if (malloc2(arr->max_size * arr->bytes, (void **) &new))
		return (2);
	arr_set(&global()->allocs, index, &new);
	mem_ncpy(new, arr->elements, arr->size * arr->bytes);
	free(arr->elements);
	arr->elements = new;
	return (0);
}

int	arr_add(t_array *arr, void *element)
{
	void	*ptr;

	if (arr->size == arr->max_size && arr_grow(arr))
		return (1);
	ptr = arr->elements + arr->size * arr->bytes;
	mem_ncpy(ptr, element, arr->bytes);
	arr->size++;
	return (0);
}

int	arr_insert_at(t_array *arr, unsigned long index, void *element)
{
	void	*dst;
	void	*src;
	size_t	len;

	if (arr->size == arr->max_size && arr_grow(arr))
		return (1);
	dst = arr_get(arr, index + 1);
	src = arr_get(arr, index);
	len = (arr->size - index) * arr->bytes;
	mem_nmov(dst, src, len);
	mem_ncpy(src, element, arr->bytes);
	arr->size++;
	return (0);
}

int	arr_insert_arr(t_array *dst, unsigned long index, t_array *src)
{
	unsigned long	i;
	void			*tmp;

	i = 0;
	while (i < arr_size(src))
	{
		tmp = arr_get(src, i);
		if (arr_insert_at(dst, index + i, tmp))
			return (1);
		i++;
	}
	return (0);
}
