#include "str.h"

int	str_starts_with(char *str, const char *match)
{
	return (str_ncmp(str, match, str_len(match)) == 0);
}
