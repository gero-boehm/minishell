#include "memory.h"

int	str_char_repeat(char c, size_t count, char **str)
{
	unsigned long	i;

	if (mem_alloc_str(count, str))
		return (1);
	i = 0;
	while (i < count)
		(*str)[i++] = c;
	return (0);
}
