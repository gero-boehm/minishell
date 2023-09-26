#include "assocdef.h"
#include "array.h"
#include "str.h"

int	assoc_index(t_assoc *assoc, const char *match, unsigned long *index)
{
	char	*key;

	*index = 0;
	while (*index < arr_size(&assoc->keys))
	{
		key = *(char **) arr_get(&assoc->keys, *index);
		if (str_eq(key, match))
			return (0);
		(*index)++;
	}
	return (1);
}
