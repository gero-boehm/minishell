#include <stddef.h>
#include <stdio.h>
#include "assocdef.h"
#include "array.h"

void	assoc_print(t_assoc *assoc)
{
	unsigned long	i;
	char			*key;
	char			*value;

	i = 0;
	while (i < assoc->keys.size)
	{
		key = *(char **) arr_get(&assoc->keys, i);
		value = *(char **) arr_get(&assoc->values, i);
		printf("%-20s| %s\n", key, value);
		i++;
	}
}
