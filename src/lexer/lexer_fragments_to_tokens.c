#include "skipdef.h"
#include "array.h"
#include "range.h"
#include "str.h"

static int	lexer_omit_quote(t_range *token_range, unsigned long index, t_quote quote)
{
	unsigned long	i;
	t_array			*quote_ranges;
	t_range			*quote_range;

	i = 0;
	quote_ranges = &token_range->meta.token_data.quote_ranges;
	while (i < arr_size(quote_ranges))
	{
		quote_range = (t_range *) arr_get(quote_ranges, i);
		if (range_contains(quote_range, index))
			return (quote_range->meta.quote == quote);
		i++;
	}
	return (0);
}

static int	lexer_fragments_to_token(t_array *fragments, t_range *token_range, t_array *tokens)
{

}

int	lexer_determine_final_fragments(t_array *fragments, t_range *token_range, t_array *flags)
{
	unsigned long	i;
	char			*fragment;
	int				keep;

	// if (arr_create(flags, sizeof(int)))
	// 	return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = *(char **) arr_get(fragments, i);
		keep = 1;
		if (str_char_is_quote(*fragment))
			keep = !lexer_omit_quote(token_range, i, *fragment);
		if (arr_add(flags, &keep))
			return (2);
		i++;
	}
	return (0);
}

int	lexer_fragments_to_tokens(t_array *fragments, t_array *token_ranges, t_array *tokens)
{
	unsigned long	i;
	t_range			*token_range;

	if (arr_create(tokens, sizeof(int)))
		return (1);
	i = 0;
	while (i < arr_size(token_ranges))
	{
		token_range = (t_range *) arr_get(token_ranges, i);
		if (lexer_determine_final_fragments(fragments, token_range, tokens))
			return (2);
		i++;
	}
	return (0);
}