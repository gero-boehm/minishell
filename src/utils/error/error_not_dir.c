#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	error_not_dir(char *path)
{
	PRINT_ERROR(shell_name(), ": cd: ", path, ": Not a directory\n", NULL);
	error(1);
}

int	return_not_dir(char *path)
{
	PRINT_ERROR(shell_name(), ": cd: ", path, ": Not a directory\n", NULL);
	return (set_exit_code(1));
}
