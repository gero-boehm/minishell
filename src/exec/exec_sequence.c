#include "skipdef.h"
#include "minishell.h"
#include "array.h"
#include "global.h"

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
