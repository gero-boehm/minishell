#include <stdlib.h>
#include "global.h"
#include "array.h"

int	malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

int	mem_add(void *ptr)
{
	return (arr_add(&global()->allocs, &ptr));
}

int	mem_alloc(size_t count, void **ptr)
{
	if (malloc2(count, ptr))
		return (1);
	if (mem_add(*ptr))
		return (2);
	return (0);
}

int	mem_free(void *ptr)
{
	if (arr_remove(&global()->allocs, &ptr))
		return (1);
	free(ptr);
	return (0);
}
