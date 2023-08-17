#include "str.h"

// static void	copy_range(t_range *dst, t_range *src)
// {
// 	dst->start = src->start;
// 	dst->length = src->length;
// }

// int	str_range_to_set_exclusive(char *str, char **patterns,
// 	unsigned long start, t_range_pattern *range)
// {
// 	t_range	tmp;
// 	int		initial;

// 	initial = 1;
// 	range->start = start;
// 	range->pattern = NULL;
// 	while (*patterns != NULL)
// 	{
// 		if(str_range_to_exclusive(str, *patterns, start, &tmp))
// 		{
// 			patterns++;
// 			continue ;
// 		}
// 		if(!initial && tmp.length >= range->length)
// 		{
// 			patterns++;
// 			continue;
// 		}
// 		range->length = tmp.length;
// 		range->pattern = *patterns;
// 		initial = 0;
// 		patterns++;
// 	}
// 	return (initial);
// }

// int	str_range_of_set(char *str, char **patterns,
// 	unsigned long start, t_range *range)
// {
// 	t_range	tmp;
// 	int		initial;

// 	initial = 1;
// 	range->start = start;
// 	range->length = 0;
// 	while (*patterns != NULL)
// 	{
// 		if(str_range_of(str, *patterns++, start, &tmp))
// 			continue ;
// 		initial = 0;
// 		if(tmp.start > range->start)
// 			continue ;
// 		range->start = tmp.start;
// 		if(tmp.length <= range->length)
// 			continue ;
// 		range->length = tmp.length;
// 	}
// 	return (initial);
// }
