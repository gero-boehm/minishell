


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include <stddef.h>

void	ft_prompt(void);
int		ft_exec(char **cmd_args);

void	ft_signals(void);
void	ft_ctrlc(int sig);
void	ft_exit(void);

