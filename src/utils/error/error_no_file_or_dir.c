#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_no_file_or_dir(char *cmd)
{
	printf("%s: %s: No such file or directory\n", shell_name(), cmd);
	error(127);
}
