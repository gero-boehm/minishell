#ifndef GLOBALDEF_H
# define GLOBALDEF_H

# include "arraydef.h"
# include "assocdef.h"

typedef struct s_global {
	char	*exec_path;
	int		exit_code;
	t_array	fds;
	t_assoc	env;
	t_array	allocs;
}	t_global;

#endif