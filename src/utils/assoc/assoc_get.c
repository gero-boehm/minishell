#include "assoc.h"
#include "array.h"
#include "str.h"

int	assoc_get(t_assoc *assoc, const char *key, char **value)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < assoc_size(assoc))
	{
		tmp = *(char **) arr_get(&assoc->keys, i);
		if (str_eq(tmp, key))
			break ;
		i++;
	}
	*value = *(char **) arr_get(&assoc->values, i);
	return (0);
}

char	*assoc_get_key_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->keys, index));
}

char	*assoc_get_value_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->values, index));
}
