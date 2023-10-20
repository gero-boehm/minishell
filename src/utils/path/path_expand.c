#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "path.h"
#include "array.h"
#include "range.h"
#include "str.h"
#include "error.h"

static int	path_entry_matches_pattern(char *name, char *pattern)
{
	unsigned long	i;
	unsigned long	start;
	t_array			subpatterns;
	char			*subpattern;
	t_range			range;

	if (str_eq(pattern, "*"))
		return (1);
	if (str_split(pattern, '*', &subpatterns))
		error_fatal();
	i = 0;
	start = 0;
	while (i < arr_size(&subpatterns))
	{
		subpattern = *(char **) arr_get(&subpatterns, i);
		if (str_range_of(name, subpattern, start, &range))
			return (0);
		if (i == 0 && *pattern != '*' && range_start(&range) > 0)
			return (0);
		start = range_end(&range);
		i++;
	}
	if (pattern[str_len(pattern) - 1] != '*' && start != str_len(name))
		return (0);
	return (1);
}


static int	path_get_paths(t_array *segments, unsigned long index, t_array *paths)
{
	char			*pattern;
	char			*path;
	t_array			copy;
	DIR				*dir;
	struct dirent	*entry;

	if (index == arr_size(segments))
		return (str_from_arr(segments, "", &pattern) || arr_add(paths, &pattern));
	pattern = *(char **) arr_get(segments, index);
	if (!str_contains(pattern, "*"))
		return (path_get_paths(segments, index + 1, paths));
	if (path_resolve(segments, index, &path))
		return (2);
	if (opendir2(path, &dir))
		return (0);
	while (1)
	{
		if (readdir2(dir, &entry))
			continue ;
		if (entry == NULL)
			break ;
		if (index < arr_size(segments) - 1 && path_entry_is_file(path, entry->d_name))
			continue;
		if (str_starts_with(entry->d_name, "."))
			continue ;
		if (!path_entry_matches_pattern(entry->d_name, pattern))
			continue ;
		if (path_get_updated_segments(segments, &copy, entry->d_name, index))
			return (3);
		if (path_get_paths(&copy, index + 1, paths))
			return (4);
		arr_free_ptr(&copy);
	}
	return (0);
}

static int path_sort(char **a, char **b)
{
	return (str_cmp(*b, *a));
}

int	path_expand(char **str)
{
	t_array	segments;
	t_array	paths;

	if (!str_contains(*str, "*"))
		return (0);
	if (path_get_segments(*str, &segments))
		return (1);
	if (arr_create(&paths, sizeof(char *)))
		return (2);
	if (path_get_paths(&segments, 0, &paths))
		return (3);
	if (arr_size(&paths) == 0)
	{
		arr_free_ptr(&segments);
		arr_free_ptr(&paths);
		return (0);
	}
	if (arr_sort(&paths, path_sort))
		return (4);
	if (str_from_arr(&paths, "\n", str))
		return (5);
	arr_free_ptr(&segments);
	arr_free_ptr(&paths);
	return (0);
}
