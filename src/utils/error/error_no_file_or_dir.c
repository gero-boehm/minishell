#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_no_file_or_dir(char *path)
{
	printf("%s: %s: No such file or directory\n", shell_name(), path);
	error(127);
}

void	return_no_file_or_dir(char *path)
{
	printf("%s: %s: No such file or directory\n", shell_name(), path);
	set_exit_code(127);
}
