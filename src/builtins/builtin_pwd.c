#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "builtins.h"
#include "error.h"
#include "env.h"

int	builtin_pwd(void)
{
	char	*pwd;

	if (env_get("PWD", &pwd))
		return (134);
	printf("%s\n", pwd);
	return (0);
}
