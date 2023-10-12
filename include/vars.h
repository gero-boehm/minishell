#ifndef VARS_H
# define VARS_H

# include "arraydef.h"

int	vars_extract(const char *str, unsigned long index, unsigned long offset, t_array *vars);

int	vars_expand_str(t_array *vars, unsigned long index, char **str);
int	vars_expand_str_split(char *str, t_array *vars, unsigned long index, t_array *parts);

#endif