#include "memory.h"

int	mem_alloc_str_arr(size_t count, char ***arr)
{
	size_t	bytes;

	bytes = (count + 1) * sizeof(char *);
	if (mem_alloc(bytes, (void **) arr))
		return (1);
	(*arr)[count] = NULL;
	return (0);
}

int	mem_alloc_str(size_t count, char **str)
{
	size_t	bytes;

	bytes = count + 1;
	if (mem_alloc(bytes, (void **) str))
		return (1);
	(*str)[count] = '\0';
	return (0);
}
