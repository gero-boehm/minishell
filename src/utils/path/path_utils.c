#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "rangedef.h"
#include "path.h"
#include "array.h"
#include "error.h"
#include "str.h"

int	opendir2(const char *path, DIR **dir)
{
	*dir = opendir(path);
	return (*dir == NULL);
}

int	readdir2(DIR *dir, struct dirent **entry)
{
	errno = 0;
	*entry = readdir(dir);
	return (errno);
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
