#include <unistd.h>
#include <sys/wait.h>
#include "skipdef.h"
#include "minishell.h"
#include "array.h"
#include "error.h"
#include "converter.h"
#include "global.h"
#include "fd.h"

int	exec_chain(t_chain *chain)
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

	if (fd_dup(STDIN_FILENO, &fd_stdin))
		error_fatal();
	if (fd_dup(STDOUT_FILENO, &fd_stdout))
		error_fatal();
	while (i < arr_size(&chain->commands))
	{
		raw = (t_raw_command *) arr_get(&chain->commands, i);
		// SKIP PIPES closed properly? TODO: make sure skipping here doesn't have negative effects. like what happens if command in the middle fails, do the fds get propagated properly?
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
			if (fd_pipe(ports))
				error_fatal();
		}
		if (arr_size(&chain->commands) == 1 && cmd.type != COMMAND_EXTERNAL)
		{
			exit_code = run_builtin_in_main(&cmd);
			if (dup2(fd_stdin, STDIN_FILENO) == -1)
				error_fatal();
			if (dup2(fd_stdout, STDOUT_FILENO) == -1)
				error_fatal();
			return (exit_code);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				error_fatal();
			if (pid == 0)
				run_child(&cmd, fd, ports, i == arr_size(&chain->commands) - 1);
			else
				run_parent(&cmd, &fd, ports);
		}
		i++;
	}
	waitpid(pid, &exit_code, 0);
	i--;
	while (i--)
		wait(NULL);
	if (dup2(fd_stdin, STDIN_FILENO) == -1)
		error_fatal();
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		error_fatal();
	return (exit_code >> 8);
}
