#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

int	return_too_many_args(void)
{
	PRINT_ERROR(shell_name(), ": exit: too many arguments\n", NULL);
	return (set_exit_code(1));
}
