
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"
#include "env.h"
#include "builtins.h"
#include "array.h"
#include "cmddef.h"
#include "str.h"
#include "memory.h"
#include "error.h"

static int	get_cmd_path(t_array *paths, char *cmd, char **cmd_path)
{
	unsigned long	i;
	char			*path;

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
		builtin_exit(&command->data.builtin_exit);
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
		if (env_get("PATH", &paths_str))
			error_fatal();
		if (str_split(paths_str, ':', &paths))
			error_fatal();
		if (get_cmd_path(&paths, cmd->data.external.args[0], &cmd_path))
			error_command_not_found(cmd->data.external.args[0]);
		if (env_get_all(&env))
			error_fatal();
		if (execve(cmd_path, cmd->data.external.args, env) == -1)
			error_fatal();
	}
	else
		exec_builtin(cmd);
	return (0);
}

int	super_duper(int fd_src, int fd_dst)
{
	printf("%d -> %d\n", fd_src, fd_dst);
	if (dup2(fd_src, fd_dst) == -1)
	{
		printf("fail %d %s\n", errno, strerror(errno));
		close(fd_src);
		return (1);
	}
	close(fd_src);
	return (0);
}

int	redirect(t_command *cmd, int input, int ports[2], int last)
{
	// printf("ri %d ro %d, in %d out %d | last %d\n", cmd->fd_in, cmd->fd_out, input, ports[1], last);
	// TODO: close input and ports[1] when stdio deviates
	if (cmd->fd_in != STDIN_FILENO)
	{
		printf("1\n");
		if (super_duper(cmd->fd_in, STDIN_FILENO))
			return (1);
	}
	else if (input != STDIN_FILENO)
	{
		printf("2\n");
		if (super_duper(input, STDIN_FILENO))
			return (2);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		printf("3\n");
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			return (3);
	}
	else if (!last)
	{
		printf("4\n");
		if (super_duper(ports[1], STDOUT_FILENO))
			return (4);
	}
	return (0);
}

void	run_child(t_command *cmd, int input, int ports[2], int last)
{
	printf("=============\n");
	if (!last)
		close(ports[0]);
	if (redirect(cmd, input, ports, last))
		error_fatal();
	exec_cmd(cmd);
}

void	run_parent(t_command *cmd, int *fd, int ports[2])
{
	(void) cmd;

	close(ports[1]);
	close(*fd);
	*fd = ports[0];
	// close(cmd->fd_out);
	// cmd->fd_out = ports[0];
}

void	run_builtin_in_main(t_command *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		printf("1\n");
		if (super_duper(cmd->fd_in, STDIN_FILENO))
			error_fatal();
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		printf("3\n");
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			error_fatal();
	}
	exec_builtin(cmd);
}

int	exec_chain(t_chain *chain)
{
	int				exit_code;
	int				ports[2];
	pid_t			pid;
	t_command		*cmd;
	unsigned long	i;
	int				fd;
	// t_raw_command	*raw;
	int				stdin;
	int				stdout;

	i = 0;
	fd = 0;
	// TODO: protect this crap
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	while (i < arr_size(&chain->commands))
	{
		cmd = (t_command *) arr_get(&chain->commands, i);
		// raw = (t_raw_command *) arr_get(&chain->commands, i);
		// cmd = 2nd_parse(raw);
		if (i < arr_size(&chain->commands) - 1)
		{
			printf("create pipe\n");
			if (pipe(ports) == -1)
			{
				printf("pipe failed\n");
				error_fatal();
			}
			// printf("%d <- %d\n", ports[0], ports[1]);
		}
		// abort();
		// TODO: Handle if amount_cmds == 1 and builtin execute builtin in parent
		if (arr_size(&chain->commands) == 1 && cmd->type != COMMAND_EXTERNAL)
			run_builtin_in_main(cmd);
		else
		{
			pid = fork();
			if (pid == -1)
				perror("fork failed");
			if (pid == 0)
				run_child(cmd, fd, ports, i == arr_size(&chain->commands) - 1);
			else
				run_parent(cmd, &fd, ports);
		}
		i++;
	}
	//----------Parent process--------//
	while (i--)
		wait(&exit_code);
	// close("fd");
	// TODO: protect this crap aswell
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	return (exit_code);
}
