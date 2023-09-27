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
#include "sequence.h"
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
#include "serializer.h"
#include "base64.h"

static int parse_input(char *str, t_array *sequence)
{
	t_array fragments;
	t_array mask;
	t_array tokens;
	t_array	token_ranges;

	if (lexer_fragments_get(str, &fragments))
		return (1);
	lexer_quotes_mark(&fragments);
	if (lexer_token_mask_get(&fragments, &mask))
		return (2);
	if (lexer_token_ranges_get(&mask, &token_ranges))
		return (3);
	if (lexer_fragments_to_tokens(&fragments, &token_ranges, &tokens))
		return (4);
	if (arr_size(&tokens) == 0)
		// TODO: free arrays
		return (0);
	lexer_tokens_classify(&tokens);
	if (lexer_tokens_validate(&tokens))
		return (5);
	if (parser_parse(&tokens, sequence))
		return (6);
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
	while(1)
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
	return (bytes_read == 0);
}

void run(char *input)
{
	t_array sequence;

	// TODO: turn returns into error_fatal() and make return value reflect if there was something to parse or not (empty input);
	parse_input(input, &sequence);

	sequence_print_raw(&sequence, 0);

	// abort();

	// char *str;
	// serializer_serialize(&sequence, &str);
	// printf("\n\n%s\n\n", str);

	// // char *decoded;
	// // char *decoded2;
	// // printf("len %zu\n", str_len(str));
	// // base64_decode(str, &decoded);
	// // printf("\n\n%s\n\n", decoded);
	// // printf("len %zu\n", str_len(str));
	// // abort();
	// // base64_decode(str, &decoded2);
	// // printf("\n\n%s\n\n", decoded2);

	// t_array seq;

	// // printf("before\n");
	// // printf("str %s\n", str);
	// deserializer_deserialize(str, &seq);
	// // printf("after\n");

	// sequence_print_raw(&seq, 0);

	// abort();

	exec_sequence(&sequence);
}

int	run_subshell(char *str)
{
	t_array sequence;

	if (deserializer_deserialize(str, &sequence))
		return (1);
	exec_sequence(&sequence);
	cleanup();
	// TODO: return proper exit code (take from last chain)
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input;

	input = NULL;

	global_init(argv[0]);
	signals();

	// char	*key;
	// char	*value;

	// if (str_key_value("====", &key, &value))
	// 	return (1);
	// printf("key '%s'\n", key);
	// printf("value '%s'\n", value);
	// abort();

	// TODO: free all memory related to sequences after each iteration of following while loops

	if (argc == 2)
		return (run_subshell(argv[1]));

	if (!isatty(STDIN_FILENO))
	{
		while (1)
		{
			if (read_input(&input))
				break ;
			run(input);
		}
		cleanup();
		// TODO: return exit code from minishell
		return (0);
	}

	while (1)
	{
		if (prompt(&input))
			break ;
		// str_dup("cat <<eof", &input);
		run(input);
		// abort();
	}

	cleanup();
	return (0);
}