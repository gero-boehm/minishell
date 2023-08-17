#include "assoc.h"
#include "array.h"
#include "str.h"

int	assoc_create(t_assoc *assoc)
{
	if (arr_create(&assoc->keys, sizeof(char *)))
		return (1);
	if (arr_create(&assoc->values, sizeof(char *)))
		return (2);
	return (0);
}

int	assoc_from_str_arr(t_assoc *assoc, char **arr)
{
	char	*key;
	char	*value;

	if (assoc_create(assoc))
		return (1);
	while (*arr != NULL)
	{
		if (str_str_to_exclusive(*arr, "=", 0, &key))
			return (2);
		if (str_str_from_exclusive(*arr, "=", 0, &value))
			return (3);
		if (assoc_set(assoc, key, value))
			return (4);
		arr++;
	}
	return (0);
}
