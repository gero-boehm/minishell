#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "cmddef.h"
#include "rangedef.h"
#include "global.h"
#include "builtins.h"
#include "error.h"
#include "str.h"
#include "env.h"
#include "path.h"

static int	report_error(char *path)
{
	if (errno == ENOENT)
		return (return_no_file_or_dir(path), 1);
	if (errno == EACCES)
		return (return_permission_denied(path), 1);
	if (errno == ENOTDIR)
		return (return_not_dir(path), 1);
	printf("%s: cd: %s: %s\n", shell_name(), path, strerror(errno));
	return (set_exit_code(errno));
}

static int	dir_change(char *to, int announce)
{
	char	*current;

	errno = 0;
	if (chdir(to) == -1)
		return (report_error(to));
	if (env_get("PWD", &current))
		env_remove("OLDPWD");
	else if (env_set("OLDPWD", current))
		error_fatal();
	if (env_set("PWD", to))
		error_fatal();
	if (announce)
		printf("%s\n", to);
	return (0);
}

static int go_home(void)
{
	char	*home;

	home = path_get_home();
	return (dir_change(home, 0));
}

static int	go_back(void)
{
	char	*last;

	if (env_get("OLDPWD", &last))
		return (return_env_not_set("OLDPWD"));
	return (dir_change(last, 1));
}

int	builtin_cd(t_builtin_cd *cd)
{
	char	*path;
	char	*home;
	t_range	range;

	path = cd->path;
	if (str_eq(path, "~"))
		return (go_home());
	if (str_eq(path, "-"))
		return (go_back());
	if (str_starts_with(path, "~"))
	{
		home = path_get_home();
		range.start = 0;
		range.length = 1;
		if (str_sub_range(&path, &range, home))
			error_fatal();
	}
	return (dir_change(path, 0));
}
