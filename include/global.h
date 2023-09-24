#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
int			global_init(char *exec_name);
void		cleanup(void);
void		success(void);

#endif