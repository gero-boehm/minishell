// #include "lexer.h"
// #include "str.h"
// #include "array.h"
// #include "memory.h"

// static void	lexer_state_init(t_lexer_state *state)
// {
// 	state->mode = MODE_COMMAND;
// 	state->string_type = STRING_NONE;
// 	state->is_escaped = 0;
// }

// static int	lexer_get_command_token(t_array *fragments, t_array *tokens)
// {
// 	unsigned long	i;
// 	char			*fragment;
// 	t_token			token;

// 	fragment = *(char **) arr_get(fragments, 0);
// 	token.str = fragment;
// 	i = 1;
// 	while (i < arr_size(fragments))
// 	{

// 	}
// }

// int	lexer_get_tokens_from_fragments(t_array *fragments, t_array *tokens)
// {
// 	unsigned long	i;
// 	char			*fragment;
// 	t_lexer_state	state;

// 	i = 0;
// 	while (i < arr_size(fragments))
// 	{

// 	}
// }

// int	lexer_fragment_is_quote(char *fragment, int escaped)
// {
// 	size_t	count;

// 	if (*fragment != '\'' && *fragment != '"')
// 		return (0);
// 	count = str_len(fragment) - escaped;
// 	return (count % 2);
// }

// int	lexer_fragment_is_quote_matching(char *fragment, char quote, int escaped)
// {
// 	size_t	count;

// 	if (*fragment != quote)
// 		return (0);
// 	count = str_len(fragment) - escaped;
// 	return (count % 2);
// }

// void	lexer_toggle_quotes(char *cache, char quote)
// {
// 	if (*cache == 0)
// 		*cache = quote;
// 	else if (*cache == quote)
// 		*cache = 0;
// }

// int	lexer_fragment_is_escape_sequence(char *fragment)
// {
// 	size_t	count;

// 	if (*fragment != '\\')
// 		return (0);
// 	count = str_len(fragment);
// 	return (count % 2);
// }

// int	lexer_reduce_escape_sequence(char **fragment)
// {
// 	size_t	count;
// 	char	*new;

// 	count = (str_len(fragment) + 1) / 2;
// 	if (str_char_repeat('\\', count, &new))
// 		return (1);
// 	mem_free(*fragment);
// 	*fragment = new;
// 	return (0);
// }

// int lexer_merge_quotes_merge(t_array *fragments, unsigned long start, unsigned long end, t_array *merged)
// {
// 	unsigned long	i;
// 	char			*fragment;

// 	i = start;
// 	while (i < end)
// 	{
// 		fragment = *(char **) arr_get(fragments, i);
// 		if (*fragment != '\\')
// 		{
// 			i++;
// 			continue ;
// 		}

// 	}
// }

// int	lexer_merge_quotes_actual(t_array *fragments, unsigned long index, char quote, t_array *merged)
// {
// 	unsigned long	i;
// 	char			*fragment;
// 	int				escaped;


// 	i = index;
// 	escaped = 0;
// 	while (i < arr_size(fragments))
// 	{
// 		fragment = *(char **) arr_get(fragments, i);
// 		if (lexer_fragment_is_quote_matching(fragment, quote, escaped))
// 		{
// 			// if (str_from_arr_range(fragment, {index, i}, ))
// 		}
// 		escaped = lexer_fragment_is_escape_sequence(fragment);
// 		i++;
// 	}
// }

// int	lexer_merge_quotes(t_array *fragments, t_array *merged)
// {
// 	unsigned long	i;
// 	char			*fragment;
// 	char			quote;
// 	int				escaped;

// 	if (arr_create(merged, sizeof(char *)))
// 		return (1);
// 	i = 0;
// 	quote = 0;
// 	escaped = 0;
// 	while (i < arr_size(fragments))
// 	{
// 		fragment = *(char **) arr_get(fragments, i);
// 		if (lexer_fragment_is_quote(fragment, escaped))

// 		escaped = lexer_fragment_is_escape_sequence(fragment);
// 	}
// }

// int	lexer_get_ranges_of_quotes(t_array *fragments, t_array *ranges)
// {
// 	unsigned long	i;
// 	char			quote;
// 	char			*fragment;

// 	if (arr_create(ranges, sizeof(int)))
// 		return (1);
// 	i = 0;
// 	while (i < arr_size(fragments))
// 	{
// 		fragment = *(char **) arr_get(fragments, i);

// 		i++;
// 	}
// }

// int	lexer_merge_fragments(t_array *fragments, t_array *merged)
// {
// 	unsigned long	i;
// 	char			*fragment;
// 	char			quote;

// 	if (arr_create(merged, sizeof(char *)))
// 		return (1);
// 	i = 0;
// 	quote = 0;
// 	while (i < arr_size(fragments))
// 	{
// 		fragment = *(char **) arr_get(fragments, i);
// 		if (lexer_fragment_is_quote(fragment))
// 			lexer_toggle_quotes(&quote, *fragment);
// 	}
// }