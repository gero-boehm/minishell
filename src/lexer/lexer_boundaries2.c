#include "array.h"

int	lexer_sort_boundaries(void *element1, void *element2)
{
	int	a;
	int	b;

	a = *(int *) element1;
	b = *(int *) element2;
	return (b - a);
}

int	lexer_remove_duplicate_boundaries(t_array *boundaries)
{
	unsigned long	i;
	unsigned long	a;
	unsigned long	b;

	i = 1;
	while (i < arr_size(boundaries))
	{
		a = *(unsigned long *) arr_get(boundaries, i - 1);
		b = *(unsigned long *) arr_get(boundaries, i);
		if (b == a && arr_remove_at(boundaries, i))
			return (1);
		i++;
	}
	return (0);
}
