#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_syntax(char *token)
{
	printf("miniheaven: syntax error near unexpected token `%.1s'\n", token);
	error(258);
}

void	return_syntax(char *token)
{
	printf("miniheaven: syntax error near unexpected token `%.1s'\n", token);
	// TODO: add 258 as exit code to global
}
