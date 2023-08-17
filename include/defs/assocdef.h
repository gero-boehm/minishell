#ifndef ASSOCDEF_H
# define ASSOCDEF_H

# include "arraydef.h"

typedef struct s_assoc {
	t_array	keys;
	t_array	values;
}	t_assoc;

#endif