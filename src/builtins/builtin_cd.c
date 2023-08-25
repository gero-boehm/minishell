#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "builtins.h"
#include "error.h"
#include "cmddef.h"
#include "str.h"
#include "env.h"

static void	ret_env_not_set(char *var)
{
	printf("miniheaven: cd: %s not set\n", var);
}

static void	ret_dir_not_exist(char *dir)
{
	printf("miniheaven: cd: %s: No such file or directory\n", dir);
}

static void	ret_permission_denied(char *dir)
{
	printf("miniheaven: cd: %s: Permission denied\n", dir);
}

static void	ret_not_dir(char *path)
{
	printf("miniheaven: cd: %s: Not a directory\n", path);
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
	char	**env;

	path = cd->path;
	if (env_get_all(&env))
		error_fatal();
	if (str_eq(path, "-"))
		return (builtin_cd_go_back());
	if (path == NULL)
		return (builtin_cd_go_home());
	return (dir_change(path));

	// TODO: if str is NULL goto home
	// TODO: rebuild chdir for own environment
	// if (cd->path == NULL)
	// 	cd->path = "~";
	// if (chdir(cd->path) == -1)
	// 	error(ENOENT);
	// error(0);
	// if (str == NULL)
	// 	str = "~";
	// if (chdir(str) == -1)
	// 	error(ENOENT);
}
