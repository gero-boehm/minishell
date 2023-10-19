#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

int	return_too_many_args(int is_exit)
{
	if (is_exit)
		return (str_print_error(1, "exit: too many arguments", NULL));
	return (str_print_error(1, "too many arguments", NULL));
}
