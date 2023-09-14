#include "arraydef.h"
#include "memory.h"

void	*arr_get(t_array *arr, unsigned long index)
{
	return (arr->elements + index * arr->bytes);
}

void	arr_set(t_array *arr, unsigned long index, void *element)
{
	void	*ptr;

	ptr = arr->elements + index * arr->bytes;
	mem_ncpy(ptr, element, arr->bytes);
}
