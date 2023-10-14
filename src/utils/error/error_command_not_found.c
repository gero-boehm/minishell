#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_command_not_found(char *cmd)
{
	PRINT_ERROR(shell_name(), ": ", cmd, ": command not found\n", NULL);
	error(127);
}
