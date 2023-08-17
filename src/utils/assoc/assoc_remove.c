#include "assocdef.h"
#include "array.h"

int	assoc_remove(t_assoc *assoc, const char *key)
{
	unsigned int	index;

	if (arr_index(&assoc->keys, &key, &index))
		return (1);
	if (arr_remove_at(&assoc->keys, index))
		return (2);
	if (arr_remove_at(&assoc->values, index))
		return (2);
	return (0);
}
