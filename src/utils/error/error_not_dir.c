#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_not_dir(char *path)
{
	printf("%s: cd: %s: Not a directory\n", shell_name(), path);
	error(1);
}

int	return_not_dir(char *path)
{
	printf("%s: cd: %s: Not a directory\n", shell_name(), path);
	return (set_exit_code(1));
}
