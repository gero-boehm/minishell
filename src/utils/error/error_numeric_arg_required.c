#include "error.h"
#include "str.h"

void	error_numeric_arg_required(char *arg)
{
	str_print_error(255, "exit: ", arg, ": numeric argument required", NULL);
	error(255);
}
