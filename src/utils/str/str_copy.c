#include "str.h"

char	*str_cpy(char *dst, const char *src)
{
	char	*cursor;

	cursor = dst;
	while (*src != '\0')
		*cursor++ = *src++;
	return (dst);
}

size_t	str_cpyn(char *dst, const char *src)
{
	str_cpy(dst, src);
	return (str_len(src));
}
