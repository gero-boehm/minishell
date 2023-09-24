#include "rangedef.h"

unsigned long	range_start(t_range *range)
{
	return (range->start);
}

unsigned long	range_end(t_range *range)
{
	return (range->start + range->length);
}

size_t			range_length(t_range *range)
{
	return (range->length);
}
