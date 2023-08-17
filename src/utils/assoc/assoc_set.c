#include "assocdef.h"
#include "array.h"

static int	assoc_add(t_assoc *assoc, const char *key, char *value)
{
	if (arr_add(&assoc->keys, &key))
		return (1);
	if (arr_add(&assoc->values, &value))
		return (2);
	return (0);
}

int	assoc_set(t_assoc *assoc, const char *key, char *value)
{
	unsigned int	index;

	if (arr_index(&assoc->keys, &key, &index))
		return (assoc_add(assoc, key, value));
	arr_set(&assoc->values, index, &value);
	return (0);
}
