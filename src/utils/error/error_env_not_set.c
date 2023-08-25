#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_env_not_set(char *var)
{
	printf("miniheaven: cd: %s not set\n", var);
	error(1);
}
