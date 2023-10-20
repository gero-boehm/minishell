#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "skipdef.h"
#include "minishell.h"
#include "array.h"
#include "error.h"
#include "converter.h"
#include "global.h"
#include "fd.h"

typedef struct s_ex_chain
{
	int				exit_code;
	pid_t			pid;
	unsigned long	i;
	int				fd;
	t_raw_command	*raw;
	t_command		cmd;
	int				ports[2];
}	t_exchain;

static void	fork_procs(
		t_chain *chain, t_exchain *ex, int *fd_stdin, int *fd_stdout)
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
			fork_procs(chain, ex, fd_stdin, fd_stdout);
		ex->i++;
	}
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
	return (ex.exit_code >> 8);
}


// int	exec_chain(t_chain *chain, int *fd_stdin, int *fd_stdout)
// {
// 	int				exit_code;
// 	pid_t			pid;
// 	unsigned long	i;
// 	int				fd;


// 	fd = 0;
// 	i = 0;
// 	pid = 0;
// 	// TODO: protect this crap, also rename vars cause they seem to be replaced by compiler (see debug vars)
// 	// i, chain, stdin, stdout, exit_code, pid
// 	while (i < arr_size(&chain->commands))
// 	{
// 		t_raw_command	*raw;
// 		t_command		cmd;
// 		int				ports[2];
// 		// chain, cmd, i
// 		raw = (t_raw_command *) arr_get(&chain->commands, i);
// 		if (converter_convert(raw, &cmd))
// 		{
// 			if (arr_size(&chain->commands) == 1)
// 				return (global()->exit_code);
// 			SKIP(i);
// 		}
// 		// chain, cmd, i, ports, exit_code, stdin, stdout
// 		// // cmd, i, chain, ports
// 		if (cmd.type == COMMAND_NONE)
// 			SKIP(i);
// 		if ((i < arr_size(&chain->commands) - 1) && (fd_pipe(ports)))
// 			error_fatal();
// 		// // chain, cmd, exit_code, stdin, stdout
// 		if (arr_size(&chain->commands) == 1 && cmd.type != COMMAND_EXTERNAL)
// 		{
// 			exit_code = run_builtin_in_main(&cmd);
// 			dup_std_end(fd_stdin, fd_stdout);
// 			return (exit_code);
// 		}
// 		//pid, cmd, ports, i, chain
// 		else
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				error_fatal();
// 			if (pid == 0)
// 				run_child(&cmd, fd, ports, i == arr_size(&chain->commands) - 1);
// 			else
// 				run_parent(&cmd, &fd, ports);
// 		}
// 		i++;
// 	}
// 	waitpid(pid, &exit_code, 0);
// 	i--;
// 	while (i--)
// 		wait(NULL);
// 	return (exit_code >> 8);
// }
