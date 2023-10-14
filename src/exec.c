#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "cmddef.h"
#include "skipdef.h"
#include "minishell.h"
#include "env.h"
#include "builtins.h"
#include "array.h"
#include "str.h"
#include "memory.h"
#include "error.h"
#include "converter.h"
#include "global.h"

static int	get_cmd_path(t_array *paths, char *cmd, char **cmd_path)
{
	unsigned long	i;
	char			*path;

	if (*cmd == '\0')
		return (1);
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

int	exec_builtin(t_command *command)
{
	if (command->type == COMMAND_BUILTIN_ECHO)
		return (builtin_echo(&command->data.builtin_echo));
	else if (command->type == COMMAND_BUILTIN_CD)
		return (builtin_cd(&command->data.builtin_cd));
	else if (command->type == COMMAND_BUILTIN_PWD)
		return (builtin_pwd());
	else if (command->type == COMMAND_BUILTIN_EXPORT)
		return (builtin_export(&command->data.builtin_export));
	else if (command->type == COMMAND_BUILTIN_UNSET)
		return (builtin_unset(&command->data.builtin_unset));
	else if (command->type == COMMAND_BUILTIN_ENV)
		return (builtin_env());
	else if (command->type == COMMAND_BUILTIN_EXIT)
		return (builtin_exit(&command->data.builtin_exit));
	printf("(⊃｡•́‿•̀｡)⊃\n");
	return (127);
}

int	cmd_is_external(t_command *cmd)
{
	return (cmd->type == COMMAND_EXTERNAL);
}

int	is_local_script(char *cmd)
{
	return (str_starts_with(cmd, "/") || str_starts_with(cmd, "./") || str_starts_with(cmd, "../"));
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
		if (access(cmd_path, F_OK))
			error_no_file_or_dir(cmd_path);
		if (access(cmd_path, X_OK))
			error_permission_denied(cmd_path);
	}
	else
	{
		if (access(cmd->data.external.args[0], X_OK))
		{
			if (env_get("PATH", &paths_str))
				error_no_file_or_dir(cmd->data.external.args[0]);
			if (str_split(paths_str, ':', &paths))
				error_fatal();
			if (get_cmd_path(&paths, cmd->data.external.args[0], &cmd_path))
				error_command_not_found(cmd->data.external.args[0]);
			arr_free_ptr(&paths);
		}
		else
			cmd_path = cmd->data.external.args[0];
	}
	if (env_set("--mhss", "1"))
		error_fatal();
	if (env_get_all(&env))
		error_fatal();
	if (env_remove("--mhss"))
		error_fatal();
	errno = 0;
	if (execve(cmd_path, cmd->data.external.args, env) == -1)
		error(errno);
		// error_fatal();
	// TODO: TESTER: check if total failure is ok
}

void	exec_cmd(t_command *cmd)
{
	if (cmd_is_external(cmd))
		exec_external(cmd);
	else
		error(exec_builtin(cmd));
}

int	super_duper(int fd_src, int fd_dst)
{
	// printf("%d -> %d\n", fd_src, fd_dst);
	if (dup2(fd_src, fd_dst) == -1)
	{
		// printf("fail %d %s\n", errno, strerror(errno));
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
		if (super_duper(cmd->fd_in, STDIN_FILENO))
			return (1);
	}
	else if (input != STDIN_FILENO)
	{
		if (super_duper(input, STDIN_FILENO))
			return (2);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			return (3);
	}
	else if (!last)
	{
		if (super_duper(ports[1], STDOUT_FILENO))
			return (4);
	}
	return (0);
}

void	run_child(t_command *cmd, int input, int ports[2], int last)
{
	// printf("=============\n");
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

int	run_builtin_in_main(t_command *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			error_fatal();
	}
	// printf("pre exec_builtin\n");
	return (exec_builtin(cmd));
}

static int	exec_chain(t_chain *chain)
{
	int				exit_code;
	int				ports[2];
	pid_t			pid;
	t_raw_command	*raw;
	t_command		cmd;
	unsigned long	i;
	int				fd;
	int				fd_stdin;
	int				fd_stdout;

	i = 0;
	fd = 0;
	pid = 0;
	// TODO: protect this crap, also rename vars cause they seem to be replaced by compiler (see debug vars)
	fd_stdin = dup(STDIN_FILENO);
	fd_stdout = dup(STDOUT_FILENO);
	while (i < arr_size(&chain->commands))
	{
		// cmd = (t_command *) arr_get(&chain->commands, i);
		raw = (t_raw_command *) arr_get(&chain->commands, i);
		// TODO: make sure skipping here doesn't have negative effects. like what happens if command in the middle fails, do the fds get propagated properly?
		if (converter_convert(raw, &cmd))
		{
			if (arr_size(&chain->commands) == 1)
				return (global()->exit_code);
			SKIP(i);
		}
		if (cmd.type == COMMAND_NONE)
			SKIP(i);
		if (i < arr_size(&chain->commands) - 1)
		{
			// printf("create pipe\n");
			if (pipe(ports) == -1)
			{
				// printf("pipe failed\n");
				error_fatal();
			}
		}
		if (arr_size(&chain->commands) == 1 && cmd.type != COMMAND_EXTERNAL)
		{
			exit_code = run_builtin_in_main(&cmd);
			dup2(fd_stdin, STDIN_FILENO);
			dup2(fd_stdout, STDOUT_FILENO);
			return (exit_code);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				// TODO: handle error correctly. throw fatal error?
				perror("fork failed");
			if (pid == 0)
				run_child(&cmd, fd, ports, i == arr_size(&chain->commands) - 1);
			else
				run_parent(&cmd, &fd, ports);
		}
		i++;
	}
	//----------Parent process--------//
	// TODO: maybe do stuff like ole
	waitpid(pid, &exit_code, 0);
	i--;
	while (i--)
		wait(NULL);
	// TODO: protect this crap aswell
	dup2(fd_stdin, STDIN_FILENO);
	dup2(fd_stdout, STDOUT_FILENO);
	// printf("final exit (%d | %d)\n", exit_code, exit_code >> 8);
	return (exit_code >> 8);
}

int	exec_get_next_chain(t_array *sequence, unsigned long index, int exit_code, t_chain **chain)
{
	static t_op	last_op = OP_END;

	*chain = (t_chain *) arr_get(sequence, index);
	if ((last_op == OP_AND && exit_code != 0) || (last_op == OP_OR && exit_code == 0))
	{
		last_op = (*chain)->op;
		return (1);
	}
	last_op = (*chain)->op;
	return (0);
}

void	exec_sequence(t_array *sequence)
{
	unsigned long	i;
	int				exit_code;
	t_chain			*chain;

	i = 0;
	while (i < arr_size(sequence))
	{
		if (exec_get_next_chain(sequence, i, exit_code, &chain))
			SKIP(i);
		exit_code = exec_chain(chain);
		set_exit_code(exit_code);
		i++;
	}
}