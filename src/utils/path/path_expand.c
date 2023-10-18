#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "path.h"
#include "array.h"
#include "range.h"
#include "str.h"
#include "memory.h"
#include "error.h"

static int	opendir2(const char *path, DIR **dir)
{
	*dir = opendir(path);
	return (*dir == NULL);
}

static int	readdir2(DIR *dir, struct dirent **entry)
{
	errno = 0;
	*entry = readdir(dir);
	return (errno);
}

void	path_expand_range(char *str, t_range *range)
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

int	path_get_segments_from_boundaries(char *str, t_array *boundaries, t_array *segments)
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
		range.start = start;
		range.length = end - start;
		if (str_extract_range(str, &range, &part))
			return (1);
		if (arr_add(segments, &part))
			return (2);
		start = end;
		i++;
	}
	return (0);
}

int	path_resolve(t_array *segments, unsigned long index, char **path)
{
	char	*cwd;
	t_range	range;

	range = (t_range) {0, index};
	if (str_from_arr_range(segments, &range, "", path))
		return (1);
	if (str_starts_with(*path, "/"))
		return (0);
	range = (t_range) {0, 1};
	if (str_starts_with(*path, "~/"))
		return (str_sub_range(path, &range, path_get_home()));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (2);
	if (str_join(path, "/", cwd, *path, NULL))
		return (free(cwd), 3);
	free(cwd);
	return (0);
}

int	path_get_segments(char *str, t_array *segments)
{
	t_array	boundaries;

	if (arr_create(segments, sizeof(char *)))
		return (1);
	if (path_get_pattern_boundaries(str, &boundaries))
		return (2);
	if (arr_size(&boundaries) == 1)
		return (arr_add(segments, &str));
	if (path_get_segments_from_boundaries(str, &boundaries, segments))
		return (4);
	arr_free(&boundaries);
	return (0);
}

int	path_entry_matches_pattern(char *name, char *pattern)
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

int	path_clone_segments(t_array *segments, t_array *clone)
{
	unsigned long	i;
	char			*segment;

	if (arr_create(clone, segments->bytes))
		return (1);
	i = 0;
	while (i < arr_size(segments))
	{
		segment = *(char **) arr_get(segments, i);
		if (str_dup(segment, &segment))
			return (2);
		if (arr_add(clone, &segment))
			return (3);
		i++;
	}
	return (0);
}

int	path_get_updated_segments(t_array *segments, t_array *clone, char *name, unsigned long index)
{
	if (path_clone_segments(segments, clone))
		return (1);
	if (str_dup(name, &name))
		return (2);
	arr_set(clone, index, &name);
	return (0);
}

int	path_entry_is_file(char *dir, char *name)
{
	struct stat	buf;
	char		*path;

	if (str_join(&path, "", dir, "/", name, NULL))
		error_fatal();
	if (stat(path, &buf) == -1)
		return (1);
	return (!S_ISDIR(buf.st_mode));
}

int	path_get_paths(t_array *segments, unsigned long index, t_array *paths)
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
		// printf("%s | %d\n", entry->d_name, entry->d_type);
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
