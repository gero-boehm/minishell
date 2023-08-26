#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
char		*shell_name(void);
int			global_init(void);
void		cleanup(void);
void		success(void);

#endif