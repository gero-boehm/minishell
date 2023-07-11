
#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// *--EXECV--*
	// char *cmd_args[] = {"ls", "-l" , NULL};
	// ft_exec(cmd_args);
	// printf("exec: %i\n", ft_exec(cmd_args));
	// printf("path: %s\n", cmd_path);
	// *--PROMPT--*
	ft_prompt();
	return (0);
}