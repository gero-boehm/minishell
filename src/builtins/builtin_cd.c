#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "builtins.h"
#include "error.h"
#include "cmddef.h"

// str doesn't needs '/' before the dir name for relative but for absolute
void	builtin_cd(t_builtin_cd *cd)
{
	// TODO: if str is NULL goto home
	// TODO: rebuild chdir for own environment
	if (cd->path == NULL)
		cd->path = "~";
	if (chdir(cd->path) == -1)
		error(ENOENT);
	error(0);
	// if (str == NULL)
	// 	str = "~";
	// if (chdir(str) == -1)
	// 	error(ENOENT);
}
