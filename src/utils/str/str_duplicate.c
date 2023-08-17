#include "str.h"
#include "memory.h"

int	str_dup(const char *str, char **dup)
{
	size_t	len;

	len = str_len(str);
	if (mem_alloc_str(len, dup))
		return (1);
	str_cpyn(*dup, str);
	return (0);
}
