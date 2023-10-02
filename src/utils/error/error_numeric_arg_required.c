#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_numeric_arg_required(char *arg)
{
	printf("%s: exit: %s: numeric argument required\n", shell_name(), arg);
	error(255);
}
