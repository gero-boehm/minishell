#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "cmddef.h"
#include "global.h"
#include "builtins.h"
#include "error.h"
#include "str.h"
#include "env.h"

static void	ret_env_not_set(char *var)
{
	// printf("%s: cd: %s not set\n", shell_name(), var);
}

static void	ret_dir_not_exist(char *dir)
{
	// printf("%s: cd: %s: No such file or directory\n", shell_name(), dir);
}

static void	ret_permission_denied(char *dir)
{
	// printf("%s: cd: %s: Permission denied\n", shell_name(), dir);
}

static void	ret_not_dir(char *path)
{
	// printf("%s: cd: %s: Not a directory\n", shell_name(), path);
}

static int	dir_check(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat))
	{
		if (errno == ENOENT)
			return (ret_dir_not_exist(path), 1);
		else if (errno == EACCES)
			return (ret_permission_denied(path), 1);
		else
			error_fatal();
	}
	if (S_ISDIR(file_stat.st_mode))
		return (0);
	return (ret_not_dir(path), 1);
}

static int	dir_change(char *to)
{
	char	*old_pwd;

	if (dir_check(to))
		return (1);
	// TODO: insert path resolve function
	// TODO: handle ~ to go home
	env_get("PWD", &old_pwd);
	if (env_set("PWD", to))
		error_fatal();
	if (env_set("OLDPWD", old_pwd))
		error_fatal();
	// TODO: protect this sucker
	chdir(to);
	return (0);
}

static int	builtin_cd_go_back(void)
{
	char	*old_pwd;

	if (env_get("OLDPWD", &old_pwd))
		return (ret_env_not_set("OLDPWD"), 1);
	if (dir_change(old_pwd))
		return (1);
	printf("%s\n", old_pwd);
	return (0);
}

static int	builtin_cd_go_home(void)
{
	char	*home;

	if (env_get("HOME", &home))
		return (ret_env_not_set("HOME"), 1);
	return (dir_change(home));
}

int	builtin_cd(t_builtin_cd *cd)
{
	char	*path;

	path = cd->path;
	if (path == NULL)
		return (builtin_cd_go_home());
	if (str_eq(path, "-"))
		return (builtin_cd_go_back());
	return (dir_change(path));
}
