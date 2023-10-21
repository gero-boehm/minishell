#include "array.h"
#include "range.h"
#include "str.h"

static void	path_expand_range(char *str, t_range *range)
{
	while (range_start(range) > 0)
	{
		if (str[range_start(range) - 1] == '/')
			break ;
		range->start--;
		range->length++;
	}
	while (range_end(range) < str_len(str))
	{
		if (str[range_end(range)] == '/')
			break ;
		range->length++;
	}
}

int	path_get_pattern_boundaries(char *str, t_array *boundaries)
{
	unsigned long	start;
	t_range			range;

	if (arr_create(boundaries, sizeof(unsigned long)))
		return (1);
	start = 0;
	while (1)
	{
		if (str_range_of(str, "*", start, &range))
			break ;
		path_expand_range(str, &range);
		if (arr_add(boundaries, &range.start))
			return (2);
		start = range_end(&range);
		if (arr_add(boundaries, &start))
			return (3);
	}
	start = str_len(str);
	if (arr_add(boundaries, &start))
		return (4);
	return (0);
}

int	path_get_segments_from_boundaries(char *str, t_array *boundaries,
	t_array *segments)
{
	unsigned long	i;
	unsigned long	start;
	unsigned long	end;
	t_range			range;
	char			*part;

	i = 0;
	start = 0;
	while (i < arr_size(boundaries))
	{
		end = *(unsigned long *) arr_get(boundaries, i);
		if (start == end)
		{
			i++;
			continue ;
		}
		range = (t_range){start, end - start, (t_range_meta){0}};
		if (str_extract_range(str, &range, &part))
			return (1);
		if (arr_add(segments, &part))
			return (2);
		start = end;
		i++;
	}
	return (0);
}
