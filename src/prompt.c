#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"


// returns when *input == NULL
int	prompt(char **input)
{
	using_history();
	*input = readline(">>");
	if (*input == NULL)
		return (1);
	if (*input[0] != '\0')
		add_history(*input);
	return (0);
}
