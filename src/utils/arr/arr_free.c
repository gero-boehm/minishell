#include "array.h"
#include "memory.h"

void	arr_free(t_array *arr)
{
	mem_free(arr->elements);
	arr->size = 0;
	arr->max_size = 0;
	arr->bytes = 0;
}
