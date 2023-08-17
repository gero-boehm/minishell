#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
int			global_init(void);
void		cleanup(void);
void		error(int code);
void		success(void);

#endif