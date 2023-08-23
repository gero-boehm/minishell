#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_syntax(char *token)
{
	printf("miniheaven: syntax error near unexpected token `%s'\n", token);
	error(258);
}
