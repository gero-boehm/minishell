#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_command_not_found(char *cmd)
{
	printf("%s: %s: command not found\n", shell_name(), cmd);
	error(127);
}
