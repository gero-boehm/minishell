#include "array.h"
#include "str.h"
#include "error.h"

static int is_dir_reference(char *part)
{
	while (*part != '\0')
	{
		if (*part != '.')
			return (0);
		part++;
	}
	return (1);
}

static int dir_change(char *part, t_array *normalized)
{
	size_t	size;

	if (str_eq(part, "."))
		return (0);
	if (str_eq(part, ".."))
	{
		size = arr_size(normalized);
		if (size == 0)
			return (0);
		arr_remove_at(normalized, size - 1);
		return (0);
	}
	return (1);
}

static void path_normalize_init(char *path, t_array *parts, t_array *normalized)
{
	if (str_split(path, '/', parts))
		error_fatal();
	if (arr_create(normalized, sizeof(char *)))
		error_fatal();
}

static void path_normalize_finish(char **path, t_array *parts, t_array *normalized, int absolute)
{
	if (str_from_arr(normalized, "/", path))
		error_fatal();
	if (absolute && str_join(path, "", "/", *path, NULL))
		error_fatal();
	arr_free(parts);
	arr_free(normalized);
}

int	path_normalize(char **path)
{
	unsigned long	i;
	t_array			parts;
	t_array			normalized;
	char			*part;
	int				absolute;

	i = 0;
	absolute = **path == '/';
	path_normalize_init(*path, &parts, &normalized);
	while (i < arr_size(&parts))
	{
		part = *(char **) arr_get(&parts, i);
		if (is_dir_reference(part))
		{
			if (dir_change(part, &normalized))
				return (1);
			i++;
			continue ;
		}
		if (arr_add(&normalized, &part))
			error_fatal();
		i++;
	}
	path_normalize_finish(path, &parts, &normalized, absolute);
	return (0);
}
