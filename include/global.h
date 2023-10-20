#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
char		*shell_name(void);
int			global_init(char *exec_name);
void		cleanup(void);
void		success(void);
int			set_exit_code(int code);

#endif