#ifndef PATH_H
# define PATH_H

# include <dirent.h>
# include "arraydef.h"

int		path_normalize(char **path);

int		opendir2(const char *path, DIR **dir);
int		readdir2(DIR *dir, struct dirent **entry);
int		path_resolve(t_array *segments, unsigned long index, char **path);
int		path_entry_is_file(char *dir, char *name);
int		path_ignore(char *pattern, char *name);

int		path_get_pattern_boundaries(char *str, t_array *boundaries);
int		path_get_segments_from_boundaries(char *str, t_array *boundaries,
			t_array *segments);
int		path_get_updated_segments(t_array *segments, t_array *clone,
			char *name, unsigned long index);
int		path_get_segments(char *str, t_array *segments);

int		path_expand(char **str);

char	*path_get_home(void);

#endif