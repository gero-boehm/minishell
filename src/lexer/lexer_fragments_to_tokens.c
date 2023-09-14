#include <stdio.h>
#include "skipdef.h"
#include "lexer.h"
#include "array.h"
#include "range.h"
#include "str.h"

static int	lexer_fragment_keep(t_fragment *fragment)
{
	t_quote	quote;

	quote = *fragment->str;
	if (!str_char_is_quote(quote))
		return (1);
	return (fragment->quote != quote);
}

static int	lexer_quote_mask_get(t_array *token_fragments, t_range *token_range, t_array *mask)
{
	unsigned long	i;
	t_fragment		*fragment;
	int				keep;

	if (arr_create(mask, sizeof(int)))
		return (1);
	i = 0;
	while (i < arr_size(token_fragments))
	{
		fragment = (t_fragment *) arr_get(token_fragments, i);
		keep = lexer_fragment_keep(fragment);
		if (arr_add(mask, &keep))
			return (2);
		i++;
	}
	return (0);
}

static void	lexer_token_contained_quotes(t_array *token_fragments, t_array *masked_fragments, t_token *token)
{
	token->contained_quotes = arr_size(token_fragments) != arr_size(masked_fragments);
}

static int	lexer_token_get(t_array *fragments, t_range *token_range, t_array *tokens)
{
	t_array	token_fragments;
	t_array	quote_mask;
	t_array	masked_fragments;
	t_token	token;

	if (arr_sub(fragments, token_range, &token_fragments))
		return (1);
	if (lexer_quote_mask_get(&token_fragments, token_range, &quote_mask))
		return (2);
	if (arr_sub_mask(&token_fragments, &quote_mask, &masked_fragments))
		return (3);
	if (lexer_vars_get(&masked_fragments, &token.vars))
		return (4);
	if (str_from_arr(&masked_fragments, &token.str))
		return (5);
	token.length = str_len(token.str);
	lexer_token_contained_quotes(&token_fragments, &masked_fragments, &token);
	if (arr_add(tokens, &token))
		return (6);

	// for (unsigned long i = 0; i < arr_size(&token_fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&token_fragments, i);
	// 	printf("\"%s\", ", fragment);
	// }
	// printf("\n");

	// for (unsigned long i = 0; i < arr_size(&token_fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&token_fragments, i);
	// 	int keep = *(int *) arr_get(&quote_mask, i);
	// 	printf(" %-*d   ", str_len(fragment), keep);
	// }
	// printf("\n");

	// for (unsigned long i = 0; i < arr_size(&masked_fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&masked_fragments, i);
	// 	printf("\"%s\", ", fragment);
	// }
	// printf("\n");
	// printf("\"%s\"\n", token.str);

	// for (unsigned long i = 0; i < arr_size(&token.vars); i++)
	// {
	// 	t_range *var = (t_range *) arr_get(&token.vars, i);
	// 	printf("%s> %lu..%lu, ", var->meta.var_data.key, range_start(var), range_end(var));
	// }
	// printf("\n\n");
	return (0);
}

int	lexer_fragments_to_tokens(t_array *fragments, t_array *token_ranges, t_array *tokens)
{
	unsigned long	i;
	t_range			*token_range;

	if (arr_create(tokens, sizeof(t_token)))
		return (1);
	i = 0;
	while (i < arr_size(token_ranges))
	{
		token_range = (t_range *) arr_get(token_ranges, i);
		if (lexer_token_get(fragments, token_range, tokens))
			return (2);
		i++;
	}
	return (0);
}