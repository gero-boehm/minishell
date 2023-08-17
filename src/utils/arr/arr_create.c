#include "arraydef.h"
#include "memory.h"

int	arr_create(t_array *arr, unsigned int bytes)
{
	arr->size = 0;
	arr->max_size = 1;
	arr->bytes = bytes;
	if (mem_alloc(bytes, &arr->elements))
		return (1);
	return (0);
}