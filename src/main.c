#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
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

static int parse_input(char *str)
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
	if (parser_parse(&tokens))
		return (6);
	arr_free(&fragments);
	arr_free(&mask);
	arr_free(&tokens);
	arr_free(&token_ranges);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input;
	t_array *sequence;

	(void) argc;

	input = NULL;

	global_init(argv[0]);
	signals();

	while (1)
	{
		if (prompt(&input))
			break ;
		// str_dup("exit", &input);
		parse_input(input);

		if (arr_size(&global()->sequences) == 0)
			continue ;

		for(unsigned long i = 0; i < arr_size(&global()->sequences); i++)
		{
			t_array	*sequence = (t_array *) arr_get(&global()->sequences, i);
			sequence_print_raw(sequence, i);
		}

		sequence = (t_array *) arr_get(&global()->sequences, arr_size(&global()->sequences) - 1);
		exec_sequence(sequence);


		// TODO: clear sequences array properly by getting pointer index in allocs array and freeing everything after that index
		global()->sequences.size = 0;
		// break;
	}

	cleanup();
	return (0);
}