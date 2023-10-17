#include "arraydef.h"
#include "memory.h"

int	arr_clone(t_array *arr, t_array *clone)
{
	if (mem_alloc(arr->max_size * arr->bytes, (void **) &clone->elements))
		return (1);
	mem_ncpy(clone->elements, arr->elements, arr->size * arr->bytes);
	clone->size = arr->size;
	clone->max_size = arr->max_size;
	clone->bytes = arr->bytes;
	return (0);
}
