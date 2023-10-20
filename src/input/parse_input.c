#include "array.h"
#include "lexer.h"
#include "error.h"
#include "parser.h"
#include "minishell.h"

static void	free_arr_lexer(
		t_array *fragments, t_array *mask,
		t_array *tokens, t_array *token_ranges)
{
	arr_free(fragments);
	arr_free(mask);
	arr_free(tokens);
	arr_free(token_ranges);
}

int	parse_input(char *str, t_array *sequence)
{
	t_array	fragments;
	t_array	mask;
	t_array	tokens;
	t_array	token_ranges;

	if (lexer_fragments_get(str, &fragments))
		error_fatal();
	if (lexer_quotes_mark(&fragments))
		return (1);
	if ((lexer_token_mask_get(&fragments, &mask))
		|| (lexer_token_ranges_get(&mask, &token_ranges))
		|| (lexer_fragments_to_tokens(&fragments, &token_ranges, &tokens)))
		error_fatal();
	if (arr_size(&tokens) == 0)
		return (free_arr_lexer(&fragments, &mask, &tokens, &token_ranges), 2);
	lexer_tokens_classify(&tokens);
	if (lexer_tokens_validate(&tokens))
		return (3);
	if (parser_parse(&tokens, sequence))
		error_fatal();
	free_arr_lexer(&fragments, &mask, &tokens, &token_ranges);
	return (0);
}
