#ifndef RANGEDEF_H
# define RANGEDEF_H

# include <stddef.h>
# include "lexerdef.h"
# include "arraydef.h"

typedef struct s_var_data {
	unsigned long	index;
	char			*key;
}	t_var_data;

typedef union u_range_meta {
	t_quote			quote;
	t_var_data		var_data;
}	t_range_meta;

typedef struct s_range {
	unsigned long	start;
	size_t			length;
	t_range_meta	meta;
}	t_range;

#endif