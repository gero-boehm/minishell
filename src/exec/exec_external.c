#include <unistd.h>
#include <errno.h>
#include "minishell.h"
#include "env.h"
#include "array.h"
#include "str.h"
#include "memory.h"
#include "error.h"

static int	get_cmd_path(t_array *paths, char *cmd, char **cmd_path)
{
	unsigned long	i;
	char			*path;

	if (*cmd == '\0')
		return (1);
	if (str_eq(cmd, ".") || str_eq(cmd, ".."))
		error_command_not_found(cmd);
	i = 0;
	while (i < arr_size(paths))
	{
		path = *(char **) arr_get(paths, i);
		if (str_join(cmd_path, "", path, "/", cmd, NULL))
			error_fatal();
		if (!access(*cmd_path, X_OK))
			return (0);
		mem_free(*cmd_path);
		i++;
	}
	return (1);
}

static void	check_script_path(char *cmd_path)
{
	if (access(cmd_path, F_OK))
		error_no_file_or_dir(cmd_path);
	if (access(cmd_path, X_OK))
		error_permission_denied(cmd_path);
}

static void	fatal_checks(char **env)
{
	if (env_set("--mhss", "1"))
		error_fatal();
	if (env_get_all(env))
		error_fatal();
	if (env_remove("--mhss"))
		error_fatal();
}

void	exec_external(t_command *cmd)
{
	char		*paths_str;
	t_array		paths;
	char		**env;
	char		*cmd_path;

	if (is_local_script(cmd->data.external.args[0]))
	{
		cmd_path = cmd->data.external.args[0];
		check_script_path(cmd_path);
	}
	else
	{
		if (env_get("PATH", &paths_str))
			error_no_file_or_dir(cmd->data.external.args[0]);
		if (str_split(paths_str, ':', &paths))
			error_fatal();
		if (get_cmd_path(&paths, cmd->data.external.args[0], &cmd_path))
			error_command_not_found(cmd->data.external.args[0]);
		arr_free_ptr(&paths);
	}
	fatal_checks(&env);
	errno = 0;
	if (execve(cmd_path, cmd->data.external.args, env) == -1)
		error(errno);
}
