#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_syntax(char *token)
{
	// printf("this should not be: syntax error near unexpected token `%.1s'\n", token);
	error(258);
}

void	return_syntax(char *token)
{
	// printf("%s: syntax error near unexpected token `%.1s'\n", shell_name(), token);
	// printf("%s: syntax error near unexpected token `%s'\n", shell_name(), token);
	// TODO: add 258 as exit code to global
}
