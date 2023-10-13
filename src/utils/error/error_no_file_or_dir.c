#include <stdio.h>
#include "global.h"
#include "error.h"

// TODO: find out where this is used and if only in cd, add "cd:" to message
void	error_no_file_or_dir(char *path)
{
	printf("%s: %s: No such file or directory\n", shell_name(), path);
	error(127);
}

int	return_no_file_or_dir(char *path)
{
	printf("%s: %s: No such file or directory\n", shell_name(), path);
	return (set_exit_code(127));
}
