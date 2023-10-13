#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_env_not_set(char *var)
{
	printf("%s: cd: %s not set\n", shell_name(), var);
	error(1);
}

int	return_env_not_set(char *var)
{
	printf("%s: cd: %s not set\n", shell_name(), var);
	return (set_exit_code(1));
}
