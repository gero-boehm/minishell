#include "memory.h"

void	mem_free_str_arr(char **arr)
{
	char	**cursor;

	cursor = arr;
	while (*cursor != NULL)
		mem_free(*cursor++);
	mem_free(arr);
}
