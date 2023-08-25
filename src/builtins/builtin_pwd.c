#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "builtins.h"
#include "error.h"

void	builtin_pwd(void)
{
	char	*pwd;

	//TODO check getcwd()!
	pwd = NULL;
	pwd = getcwd(pwd, 1);
	if (pwd == NULL)
		error(errno);
	printf("%s\n", pwd);
	error(0);
}
