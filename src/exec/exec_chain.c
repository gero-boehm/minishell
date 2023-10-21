#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"
#include "array.h"
#include "error.h"
#include "converter.h"
#include "global.h"
#include "fd.h"
#include "exchain.h"

static void	fork_procs(t_chain *chain, t_exchain *ex)
{
	ex->pid = fork();
	if (ex->pid == -1)
		error_fatal();
	if (ex->pid == 0)
		run_child(&ex->cmd, ex->fd, ex->ports,
			ex->i == arr_size(&chain->commands) - 1);
	else
		run_parent(&ex->cmd, &ex->fd, ex->ports);
}

static int	handle_single_builtin(
		t_chain *chain, t_exchain *ex, int *fd_stdin, int *fd_stdout)
{
	if (arr_size(&chain->commands) == 1 && ex->cmd.type != COMMAND_EXTERNAL)
	{
		ex->exit_code = run_builtin_in_main(&ex->cmd);
		dup_std_end(fd_stdin, fd_stdout);
		return (1);
	}
	return (0);
}

int	exec_loop(t_chain *chain, t_exchain *ex, int *fd_stdin, int *fd_stdout)
{
	while (ex->i < arr_size(&chain->commands))
	{
		ex->raw = (t_raw_command *) arr_get(&chain->commands, ex->i);
		if (converter_convert(ex->raw, &ex->cmd))
		{
			if (arr_size(&chain->commands) == 1)
				return (1);
			ex->i++;
			continue ;
		}
		if (ex->cmd.type == COMMAND_NONE)
		{
			ex->i++;
			continue ;
		}
		if ((ex->i < arr_size(&chain->commands) - 1) && (fd_pipe(ex->ports)))
			error_fatal();
		if (handle_single_builtin(chain, ex, fd_stdin, fd_stdout))
			return (2);
		else
			fork_procs(chain, ex);
		ex->i++;
	}
	return (0);
}

int	exec_chain(t_chain *chain, int *fd_stdin, int *fd_stdout)
{
	t_exchain	ex;
	int			ret;

	ex.i = 0;
	ex.fd = 0;
	ex.pid = 0;
	ret = 0;
	ret = exec_loop(chain, &ex, fd_stdin, fd_stdout);
	if (ret == 1)
		return (global()->exit_code);
	else if (ret == 2)
		return (ex.exit_code);
	waitpid(ex.pid, &ex.exit_code, 0);
	ex.i--;
	while (ex.i--)
		wait(NULL);
	return (WEXITSTATUS(ex.exit_code));
}
