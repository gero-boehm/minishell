#ifndef PATH_H
# define PATH_H

# include "arraydef.h"

int		path_normalize(char **path);

int		path_expand(char **str);

char	*path_get_home(void);

#endif