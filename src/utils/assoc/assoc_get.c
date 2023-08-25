#include "assoc.h"
#include "array.h"
#include "str.h"

int	assoc_get(t_assoc *assoc, const char *key, char **value)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (i < assoc_size(assoc))
	{
		tmp = *(char **) arr_get(&assoc->keys, i);
		if (str_eq(tmp, key))
		{
			*value = *(char **) arr_get(&assoc->values, i);
			return (*value == NULL);
		}
		i++;
	}
	*value = NULL;
	return (2);
}

char	*assoc_get_key_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->keys, index));
}

char	*assoc_get_value_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->values, index));
}
