#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>
#include "globaldef.h"
#include "global.h"
#include "array.h"
#include "assoc.h"
#include "memory.h"
#include "env.h"
#include "str.h"
#include "wildcard.h"
#include "tmp.h"
#include "vars.h"
#include "lexer.h"
#include "error.h"
#include "range.h"
#include "token.h"
#include "parser.h"
#include "number.h"
#include "path.h"
#include "minishell.h"
#include "deserializer.h"
#include "base64.h"
#include "fd.h"

static int	parse_input(char *str, t_array *sequence)
{
	t_array	fragments;
	t_array	mask;
	t_array	tokens;
	t_array	token_ranges;

	if (lexer_fragments_get(str, &fragments))
		error_fatal();
	if (lexer_quotes_mark(&fragments))
		return (1);
	if (lexer_token_mask_get(&fragments, &mask))
		error_fatal();
	if (lexer_token_ranges_get(&mask, &token_ranges))
		error_fatal();
	if (lexer_fragments_to_tokens(&fragments, &token_ranges, &tokens))
		error_fatal();
	if (arr_size(&tokens) == 0)
		// TODO: free arrays
		return (2);
	lexer_tokens_classify(&tokens);
	if (lexer_tokens_validate(&tokens))
		return (3);
	if (parser_parse(&tokens, sequence))
		error_fatal();
	arr_free(&fragments);
	arr_free(&mask);
	arr_free(&tokens);
	arr_free(&token_ranges);
	return (0);
}

int	read_input(char **str)
{
	unsigned long	i;
	t_array			letters;
	char			letter;
	int				bytes_read;

	if (arr_create(&letters, sizeof(char)))
		error_fatal();
	while (1)
	{
		bytes_read = read(STDIN_FILENO, &letter, 1);
		if (bytes_read < 0)
			error_fatal();
		if (bytes_read == 0 || letter == '\n')
			break ;
		if (arr_add(&letters, &letter))
			error_fatal();
	}
	if (mem_alloc_str(arr_size(&letters), str))
		error_fatal();
	i = 0;
	while (i < arr_size(&letters))
	{
		(*str)[i] = *(char *) arr_get(&letters, i);
		i++;
	}
	arr_free(&letters);
	return (str_len(*str) == 0 && bytes_read == 0);
}

void	run(char *input)
{
	t_array			sequence;
	unsigned long	index;

	index = arr_size(&global()->allocs);
	// TODO: turn returns into error_fatal() and make return value reflect if there was something to parse or not (empty input);
	if (parse_input(input, &sequence))
	{
		// mem_free_from(index);
		fd_close_all();
		return ;
	}
	exec_sequence(&sequence);
	// TODO: find a better way to implement this. cause this messes up export since the keys and values are assigned after index and are thus cleared..
	// mem_free_from(index);
	fd_close_all();
}

int	run_subshell(char *str)
{
	t_array	sequence;

	if (deserializer_deserialize(str, &sequence))
		error_fatal();
	exec_sequence(&sequence);
	cleanup();
	return (global()->exit_code);
}

int	main(int argc, char **argv)
{
	char	*input;

	input = NULL;
	global_init(argv[0]);
	signals();

	// TODO: free all memory related to sequences after each iteration of following while loops

	if (argc == 2 && !env_get("--mhss", NULL))
		return (run_subshell(argv[1]));
	if (argc > 1)
	{
		cleanup();
		return (return_too_many_args(0));
	}

	if (!isatty(STDIN_FILENO))
	{
		while (1)
		{
			if (read_input(&input))
				break ;
			run(input);
		}
		cleanup();
		return (global()->exit_code);
	}

	while (1)
	{
		if (prompt(&input))
			break ;
		run(input);
	}
	cleanup();
	return (0);
}
