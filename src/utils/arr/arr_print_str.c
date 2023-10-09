#include <stdio.h>
#include "array.h"

void	arr_print_str(t_array *arr)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < arr_size(arr))
	{
		tmp = *(char **) arr_get(arr, i);
		printf("\"%s\"", tmp);
		if (i < arr_size(arr) - 1)
			printf(", ");
		i++;
	}
	printf("\n");
}
