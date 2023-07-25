
#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "arraydef.h"

int		prompt(char **input);
int		exec(t_array *sequence);

void	signals(void);
void	ctrlc(int sig);

#endif
