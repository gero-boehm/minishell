#ifndef FRAGMENT_H
# define FRAGMENT_H

#include <stddef.h>
#include "fragmentdef.h"
#include "arraydef.h"

int		fragment_is_escaped(t_array *fragments, unsigned long index);
size_t	fragment_quote_count(t_array *fragments, unsigned long index, t_quote quote, int ignore_escape);
int		fragment_is_quote_matching(char *fragment, t_quote quote);

#endif