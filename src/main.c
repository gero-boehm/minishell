#include <unistd.h>
#include "global.h"
#include "array.h"
#include "env.h"
#include "error.h"
#include "minishell.h"
#include "deserializer.h"
#include "fd.h"
#include "memory.h"

#include <stdlib.h>
#include "str.h"

void	sequence_print_raw(t_array *sequence, unsigned long index);


void	run(char *input)
{
	t_array			sequence;
	unsigned long	index;

	// TODO: turn returns into error_fatal() and make return value reflect if there was something to parse or not (empty input);
	if (parse_input(input, &sequence))
	{
		if (!arr_index(&global()->allocs, &global()->exec_path, &index))
			mem_free_from(++index);
		fd_close_all();
		return ;
	}
	// sequence_print_raw(&sequence, 0);
	exec_sequence(&sequence);
	// TODO: find a better way to implement this. cause this messes up export since the keys and values are assigned after index and are thus cleared..
	if (!arr_index(&global()->allocs, &global()->exec_path, &index))
		mem_free_from(++index);
	fd_close_all();
}

int	run_subshell(char *str)
{
	t_array			sequence;

	if (deserializer_deserialize(str, &sequence))
		error_fatal();
	exec_sequence(&sequence);
	cleanup();
	return (global()->exit_code);
}

static void	infinite_read(char **input)
{
	while (1)
	{
		if (read_input(input))
			break ;
		run(*input);
	}
}

static void	infinite_prompt(char **input)
{
	while (1)
	{
		// str_dup("export A=5", input);
		if (prompt(input))
			break ;
		run(*input);
		// abort();
	}
}

int	main(int argc, char **argv)
{
	char	*input;

	input = NULL;
	global_init(argv[0]);
	signals();
	if (argc == 2 && !env_get("--mhss", NULL))
		return (run_subshell(argv[1]));
	if (argc > 1)
		return (cleanup(), return_too_many_args(0));
	if (!isatty(STDIN_FILENO))
	{
		infinite_read(&input);
		cleanup();
		return (global()->exit_code);
	}
	infinite_prompt(&input);
	cleanup();
	return (0);
}
