#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "builtins.h"
#include "error.h"
#include "cmddef.h"
#include "str.h"
#include "env.h"

static void	builtin_cd_go_back(void)
{
	char	*pwd;
	char	*old_pwd;

	if (env_get("OLDPWD", &old_pwd))
		error_env_not_set("OLDPWD");
	if (env_get("PWD", &pwd))
		error_fatal();
	if (env_set("PWD", old_pwd))
		error_fatal();
	if (env_set("OLDPWD", pwd))
		error_fatal();
	printf("%s\n", old_pwd);
}

static void	builtin_cd_go_home(void)
{
	char	*home;
	char	*old_pwd;

	if (env_get("HOME", &home))
		error_env_not_set("HOME");
	if (env_get("PWD", &old_pwd))
		error_fatal();
	if (env_set("PWD", home))
		error_fatal();
	if (env_set("OLDPWD", old_pwd))
		error_fatal();
	success();
}

void	builtin_cd(t_builtin_cd *cd)
{
	char	*path;
	char	**env;

	path = cd->path;
	if (env_get_all(&env))
		error_fatal();
	if (str_eq(path, "-"))
		builtin_cd_go_back();
	if (path == NULL)
		builtin_cd_go_home();

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
