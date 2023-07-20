
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

int		prompt(char **input);
int		exec(char **cmd_args);

void	signals(void);
void	ctrlc(int sig);

#endif
