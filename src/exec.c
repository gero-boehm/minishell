#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "env.h"
#include "global.h"
#include "builtins.h"
#include "array.h"
#include "cmddef.h"
#include "str.h"
#include "memory.h"

static int	get_cmd_path(t_array *paths, char *cmd, char **cmd_path)
{
	unsigned long	i;
	char			*path;

	i = 0;
	while (i < arr_size(paths))
	{
		path = *(char **) arr_get(paths, i);
		if (str_join(cmd_path, "", path, "/", cmd, NULL))
			error(134);
		if (!access(*cmd_path, X_OK))
			return (0);
		mem_free(*cmd_path);
		i++;
	}
	return (1);
}

void	exec_builtin(t_command *command)
{
	if (command->type == COMMAND_BUILTIN_ECHO)
		builtin_echo(&command->data.builtin_echo);
	else if (command->type == COMMAND_BUILTIN_CD)
		builtin_cd(&command->data.builtin_cd);
	else if (command->type == COMMAND_BUILTIN_PWD)
		builtin_pwd();
	else if (command->type == COMMAND_BUILTIN_EXPORT)
		builtin_export(&command->data.builtin_export);
	else if (command->type == COMMAND_BUILTIN_UNSET)
		builtin_unset(&command->data.builtin_unset);
	else if (command->type == COMMAND_BUILTIN_ENV)
		builtin_env();
	else if (command->type == COMMAND_BUILTIN_EXIT)
		builtin_exit();
}

int	exec_cmd(t_command *cmd)
{
	char		*paths_str;
	t_array		paths;
	char		**env;
	char		*cmd_path;

	if (cmd->type == COMMAND_EXTERNAL)
	{
		//TODO: find proper exit code
		if (env_get_all(&env))
			error(134);
		if (env_get("PATH", &paths_str))
			error(134);
		if (str_split(paths_str, ':', &paths))
			error(134);
		if (get_cmd_path(&paths, cmd->data.external.args[0], &cmd_path))
		{
			printf("bash: %s: command not found\n", cmd->data.external.args[0]);
			error(127);
		}
		execve(cmd_path, cmd->data.external.args, env);
	}
	else
		exec_builtin(cmd);
	return (0);
}

void	run_child(t_command *cmd, int port)
{
	// close(ports[0]);
	// dup2("fd", STDIN);
	// dup2(ports[1], STDOUT);
	// close("fd");
	// close(ports[1]);
	// if ("fd" == -1)
	// 	return ;
	exec_cmd(cmd);
}

void	run_parent(t_command *command, int port)
{
	// close(ports[1]);
	// close("fd");
	// "fd" = ports[0];
}

//TODO mem_alloc amount_cmds
int	exec_chain(t_chain *chain)
{
	pid_t			pid;
	int				ports[2];
	int				i;
	// int				amount_cmds;
	// t_raw_command	*raw;
	t_command		*cmd;
	int				exit_code;

	// amount_cmds = arr_size(&chain->commands);
	i = 0;
	while (i < arr_size(&chain->commands))
	{
		cmd = (t_command *) arr_get(&chain->commands, i);
		// raw = (t_raw_command *) arr_get(&chain->commands, i);
		// cmd = 2nd_parse(raw);
		// if (amount_cmds - 1 > i)
		// 	if (pipe(ports) == -1)
		// 		perror("pipe failed");
		pid = fork();
		if (pid == -1)
			perror("fork failed");
		if (pid == 0)
			run_child(cmd, ports[1]);
		else
			run_parent(cmd, ports[0]);
		i++;
	}
	//----------Parent process--------//
	wait(&exit_code);
	//--------------------------------//
	// close("fd");
	return (exit_code);
}
