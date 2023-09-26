#include "arraydef.h"

#ifndef VARS_H
# define VARS_H

int	vars_expand_str(t_array *vars, unsigned long index, char **str);
int	vars_expand_str_arr(t_array *vars, char **str);

#endif