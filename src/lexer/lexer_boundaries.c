#include <stdio.h>
#include "lexerdef.h"
#include "array.h"
#include "str.h"

static char *symbols[] = {" \n\t\r\f\v", "\"", "&", "'", "(", ")", "<", ">", "|", NULL};

static int	lexer_get_ranges_of_set(char *str, char *set, t_array *boundaries)
{
	t_range			range;
	unsigned long	start;
	unsigned long	end;

	start = 0;
	while (!str_range_of_set(str, set, start, &range))
	{
		if (arr_add(boundaries, &range.start))
			return (1);
		end = range.start + range.length;
		if (arr_add(boundaries, &end))
			return (2);
		start = end;
	}
	return (0);
}

static int	lexer_get_ranges_of_sets(char *str, char **sets, t_array *boundaries)
{
	while (*sets != NULL)
	{
		if (lexer_get_ranges_of_set(str, *sets, boundaries))
			return (1);
		sets++;
	}
	return (0);
}


static int	lexer_sort_boundaries(void *element1, void *element2)
{
	int a = *(int *) element1;
	int b = *(int *) element2;

	return (b - a);
}

static int lexer_remove_duplicate_boundaries(t_array *boundaries)
{
	unsigned long	i;
	unsigned long	a;
	unsigned long	b;

	i = 1;
	while (i < arr_size(boundaries))
	{
		a = *(unsigned long*) arr_get(boundaries, i - 1);
		b = *(unsigned long*) arr_get(boundaries, i);
		if (b == a && arr_remove_at(boundaries, i))
			return (1);
		i++;
	}
	return (0);
}

int	lexer_boundaries_get(char *str, t_array *boundaries)
{
	size_t	len;

	if (arr_create(boundaries, sizeof(unsigned long)))
		return (1);
	if (lexer_get_ranges_of_sets(str, symbols, boundaries))
		return (2);
	if (arr_sort(boundaries, lexer_sort_boundaries))
		return (3);
	for (unsigned long i = 0; i < arr_size(boundaries); i++)
		printf("%lu ", *(unsigned long *) arr_get(boundaries, i));
	printf("\n");
	len = str_len(str);
	if (arr_add(boundaries, &len))
		return (4);
	if (lexer_remove_duplicate_boundaries(boundaries))
		return (5);
}
