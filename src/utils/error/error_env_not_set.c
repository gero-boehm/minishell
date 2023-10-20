#include "error.h"
#include "str.h"

void	error_env_not_set(char *var)
{
	str_print_error(1, "cd: ", var, " not set", NULL);
	error(1);
}

int	return_env_not_set(char *var)
{
	return (str_print_error(1, "cd: ", var, " not set", NULL));
}
