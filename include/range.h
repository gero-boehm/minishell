#ifndef RANGE_H
# define RANGE_H

# include "rangedef.h"

unsigned long	range_start(t_range *range);
unsigned long	range_end(t_range *range);
size_t			range_length(t_range *range);

int				range_contains(t_range *range, unsigned long index);
int				range_contains_range(t_range *outside, t_range *inside);


#endif