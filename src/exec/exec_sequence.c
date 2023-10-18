#include <unistd.h>
#include "skipdef.h"
#include "minishell.h"
#include "array.h"
#include "global.h"
#include "error.h"
#include "fd.h"

void	dup_std_start(int *fd_stdin, int *fd_stdout)
{
	if (fd_dup(STDIN_FILENO, fd_stdin) || fd_dup(STDOUT_FILENO, fd_stdout))
		error_fatal();
}

void	dup_std_end(int *fd_stdin, int *fd_stdout)
{
	if ((dup2(*fd_stdin, STDIN_FILENO) == -1)
		|| (dup2(*fd_stdout, STDOUT_FILENO) == -1))
		error_fatal();
}

static int	exec_get_next_chain(
		t_array *sequence, unsigned long index, int exit_code, t_chain **chain)
{
	static t_op	last_op = OP_END;

	*chain = (t_chain *) arr_get(sequence, index);
	if ((last_op == OP_AND && exit_code != 0)
		|| (last_op == OP_OR && exit_code == 0))
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
	int				fd_stdin;
	int				fd_stdout;

	i = 0;
	while (i < arr_size(sequence))
	{
		if (exec_get_next_chain(sequence, i, exit_code, &chain))
			SKIP(i);

		dup_std_start(&fd_stdin, &fd_stdout);
		exit_code = exec_chain(chain, &fd_stdin, &fd_stdout);
		dup_std_end(&fd_stdin, &fd_stdout);

		// exit_code = exec_chain(chain);
		set_exit_code(exit_code);
		i++;
	}
}

// void	exec_sequence(t_array *sequence)
// {
// 	unsigned long	i;
// 	int				exit_code;
// 	t_chain			*chain;

// 	i = 0;
// 	while (i < arr_size(sequence))
// 	{
// 		if (exec_get_next_chain(sequence, i, exit_code, &chain))
// 			SKIP(i);
// 		exit_code = exec_chain(chain);
// 		set_exit_code(exit_code);
// 		i++;
// 	}
// }