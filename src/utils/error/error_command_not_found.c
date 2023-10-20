#include "error.h"
#include "str.h"

void	error_command_not_found(char *cmd)
{
	str_print_error(127, cmd, ": command not found", NULL);
	error(127);
}
