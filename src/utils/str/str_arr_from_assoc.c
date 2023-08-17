#include "assoc.h"
#include "str.h"
#include "memory.h"

static int	assoc_get_str_at(t_assoc *assoc, unsigned int index, char **str)
{
	char	*cursor;
	char	*key;
	char	*value;
	size_t	len;

	key = assoc_get_key_at(assoc, index);
	value = assoc_get_value_at(assoc, index);
	len = str_len(key) + str_len(value) + 1;
	if (mem_alloc_str(len, str))
		return (1);
	cursor = *str;
	cursor += str_cpyn(cursor, key);
	cursor += str_cpyn(cursor, "=");
	cursor += str_cpyn(cursor, value);
	return (0);
}

int	assoc_to_str_arr(t_assoc *assoc, char ***arr)
{
	unsigned long	i;

	if (mem_alloc_str_arr(assoc_size(assoc), arr))
		return (1);
	i = 0;
	while (i < assoc_size(assoc))
	{
		if (assoc_get_str_at(assoc, i, *arr + i))
			return (2);
		i++;
	}
	return (0);
}
