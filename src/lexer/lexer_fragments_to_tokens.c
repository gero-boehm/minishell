#include <stdio.h>
#include "skipdef.h"
#include "array.h"
#include "range.h"
#include "str.h"

static int	lexer_fragment_keep(char *fragment, unsigned long index, t_array *quote_ranges)
{
	unsigned long	i;
	t_range			*quote_range;

	if (!str_char_is_quote(*fragment))
		return (1);
	i = 0;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_range *) arr_get(quote_ranges, i);
		if (range_contains(quote_range, index))
			return (quote_range->meta.quote != *fragment);
		i++;
	}
	return (1);
}

static int	lexer_token_mask_get(t_array *token_fragments, t_range *token_range, t_ranges *ranges, t_array *mask)
{
	unsigned long	i;
	char			*fragment;
	int				keep;

	if (arr_create(mask, sizeof(int)))
		return (1);
	i = 0;
	while (i < arr_size(token_fragments))
	{
		fragment = *(char **) arr_get(token_fragments, i);
		keep = lexer_fragment_keep(fragment, i + range_start(token_range), &ranges->quote_ranges);
		if (arr_add(mask, &keep))
			return (2);
		i++;
	}
	return (0);
}

static int	lexer_token_get(t_array *fragments, t_range *token_range, t_ranges *ranges, t_array *tokens)
{
	t_array	token_fragments;
	t_array	token_mask;
	t_array	masked_fragments;
	t_token	token;

	if (arr_sub(fragments, token_range, &token_fragments))
		return (1);
	if (lexer_token_mask_get(&token_fragments, token_range, ranges, &token_mask))
		return (2);
	if (arr_sub_mask(&token_fragments, &token_mask, &masked_fragments))
		return (3);
	if (str_from_arr(&masked_fragments, &token.str))
		return (4);
	token.length = str_len(token.str);
	if (arr_add(tokens, &token))
		return (5);

	for (unsigned long i = 0; i < arr_size(&token_fragments); i++)
	{
		char *fragment = *(char **) arr_get(&token_fragments, i);
		printf("\"%s\", ", fragment);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&token_fragments); i++)
	{
		char *fragment = *(char **) arr_get(&token_fragments, i);
		int keep = *(int *) arr_get(&token_mask, i);
		printf(" %-*d   ", str_len(fragment), keep);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&masked_fragments); i++)
	{
		char *fragment = *(char **) arr_get(&masked_fragments, i);
		printf("\"%s\", ", fragment);
	}
	printf("\n");
	printf("%s\n", token.str);
	return (0);
}


int	lexer_fragments_to_tokens(t_array *fragments, t_ranges *ranges, t_array *tokens)
{
	unsigned long	i;
	t_range			*token_range;


	if (arr_create(tokens, sizeof(t_token)))
		return (1);
	i = 0;
	while (i < arr_size(&ranges->token_ranges))
	{
		token_range = (t_range *) arr_get(&ranges->token_ranges, i);
		if (lexer_token_get(fragments, token_range, ranges, tokens))
			return (2);
		i++;
	}
	return (0);
}