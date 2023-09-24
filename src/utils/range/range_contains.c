#include "range.h"

int	range_contains(t_range *range, unsigned long index)
{
	return (range_start(range) <= index && range_end(range) > index);
}

int	range_contains_range(t_range *outside, t_range *inside)
{
	if (range_start(inside) < range_start(outside))
		return (0);
	if (range_end(inside) > range_end(outside))
		return (0);
	return (1);
}
