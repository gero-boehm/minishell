#include <stdio.h>
#include "global.h"
#include "error.h"

void	error_permission_denied(char *path)
{
	printf("%s: cd: %s: Permission denied\n", shell_name(), path);
	error(126);
}

int	return_permission_denied(char *path)
{
	printf("%s: cd :%s: Permission denied\n", shell_name(), path);
	return (set_exit_code(126));
}
