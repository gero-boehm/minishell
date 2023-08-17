#include "array.h"
#include "memory.h"

int	arr_index(t_array *arr, void *element, unsigned int *index)
{
	unsigned int	i;
	void			*tmp;

	i = 0;
	while (i < arr->size)
	{
		tmp = arr_get(arr, i);
		if (mem_ncmp(tmp, element, arr->bytes) == 0)
		{
			if (index != NULL)
				*index = i;
			return (0);
		}
		i++;
	}
	return (1);
}
