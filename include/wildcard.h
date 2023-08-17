#ifndef WILDCARD_H
# define WILDCARD_H

# include "arraydef.h"

int	get_paths(char *pattern, t_array *paths);


int	is_pattern_matching(char *name, char *pattern);


#endif