
#include "../include/minishell.h"

void	ft_signals(void)
{
	signal(SIGINT, &ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		// printf("%i %s", "\n");
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_exit(void)
{
	printf("%s\n", "exit");
	clear_history();
	exit(0);
}