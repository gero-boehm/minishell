#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_command_not_found(char *cmd)
{
	printf("happy_hippo: %s: command not found\n", cmd);
	error(127);
}