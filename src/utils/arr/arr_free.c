#include "array.h"
#include "memory.h"

void	arr_free(t_array *arr)
{
	mem_free(arr->elements);
	arr->size = 0;
	arr->max_size = 0;
	arr->bytes = 0;
}

void	arr_free_ptr(t_array *arr)
{
	unsigned long	i;
	void			*ptr;

	i = 0;
	while (i < arr_size(arr))
	{
		ptr = *(void **) arr_get(arr, i);
		mem_free(ptr);
		i++;
	}
	arr_free(arr);
}
