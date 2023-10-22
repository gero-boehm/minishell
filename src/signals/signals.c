#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "error.h"
#include "minishell.h"

static void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
