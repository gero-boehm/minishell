#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_env_not_set(char *var)
{
	PRINT_ERROR(shell_name(), ": cd: ", var, " not set\n", shell_name(), var);
	error(1);
}

int	return_env_not_set(char *var)
{
	PRINT_ERROR(shell_name(), ": cd: ", var, " not set\n", shell_name(), var);
	return (set_exit_code(1));
}
