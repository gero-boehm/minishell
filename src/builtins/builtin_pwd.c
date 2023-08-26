#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "builtins.h"
#include "error.h"
#include "env.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
		error_fatal();
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
