#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_permission_denied(char *path)
{
	PRINT_ERROR(shell_name(), ": ", path, ": Permission denied\n", NULL);
	error(126);
}

int	return_permission_denied(char *path)
{
	PRINT_ERROR(shell_name(), ": ", path, " :%s: Permission denied\n", NULL);
	return (set_exit_code(126));
}
