#include "assoc.h"
#include "array.h"

int	assoc_remove(t_assoc *assoc, const char *key)
{
	unsigned long	index;

	if (assoc_index(assoc, key, &index))
		return (0);
	if (arr_remove_at(&assoc->keys, index))
		return (1);
	if (arr_remove_at(&assoc->values, index))
		return (2);
	return (0);
}
