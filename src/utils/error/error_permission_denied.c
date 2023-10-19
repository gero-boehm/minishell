#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_permission_denied(char *path)
{
	str_print_error(126, path, ": Permission denied", NULL);
	error(126);
}

int	return_permission_denied(char *path)
{
	return (str_print_error(126, path, ": Permission denied", NULL));
}
