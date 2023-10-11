#include "rangedef.h"
#include "str.h"

int	str_contains(const char *str, const char *match)
{
	t_range	range;

	return (!str_range_of(str, match, 0, &range));
}
