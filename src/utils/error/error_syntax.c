#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_syntax_ret(char *token)
{
	printf("miniheaven: syntax error near unexpected token `%.1s'\n", token);
	// TODO: store exit code in global
	// error(258);
}
