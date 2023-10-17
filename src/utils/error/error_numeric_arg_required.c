#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_numeric_arg_required(char *arg)
{
	PRINT_ERROR(shell_name(),
		": exit: ", arg, ": numeric argument required\n", NULL);
	error(255);
}
