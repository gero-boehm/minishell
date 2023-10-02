#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft.h"
# include "arraydef.h"
# include "cmddef.h"

int		prompt(char **input);
void	exec_sequence(t_array *sequence);

int		read_input(char **str);

void	signals(void);
void	ctrlc(int sig);

#endif
