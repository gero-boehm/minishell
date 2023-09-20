#ifndef GLOBALDEF_H
# define GLOBALDEF_H

# include "arraydef.h"
# include "assocdef.h"

typedef struct s_global {
	t_array	fds;
	t_assoc	env;
	t_array	allocs;
	t_array	heredocs;
	t_array	sequences;
}	t_global;

int	g_signal;

#endif