#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

// TODO: find out where this is used and if only in cd, add "cd:" to message
void	error_no_file_or_dir(char *path)
{
	PRINT_ERROR(shell_name(), ": ", path, ": No such file or directory\n", NULL);
	error(127);
}

int	return_no_file_or_dir(char *path)
{
	PRINT_ERROR(shell_name(), ": ", path, ": No such file or directory\n", NULL);
	return (set_exit_code(127));
}
