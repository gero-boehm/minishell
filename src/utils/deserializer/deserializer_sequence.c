#include "cmddef.h"
#include "deserializer.h"
#include "array.h"

int	deserializer_deserialize_sequence(t_array *lines, unsigned long *index, t_array *sequence)
{
	t_chain	chain;

	if (arr_create(sequence, sizeof(t_chain)))
		return (1);
	while (1)
	{
		if (!line_matches(lines, *index, "chain"))
			break ;
		(*index)++;
		if (deserializer_deserialize_chain(lines, index, &chain))
			return (2);
		if (arr_add(sequence, &chain))
			return (3);
	}
	return (0);
}
