#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft.h"
# include "arraydef.h"
# include "cmddef.h"

int		prompt(char **input);
int		exec_chain(t_chain *chain);

void	signals(void);
void	ctrlc(int sig);

#endif
