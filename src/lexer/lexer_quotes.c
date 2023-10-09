#include "skipdef.h"
#include "lexerdef.h"
#include "array.h"
#include "str.h"
#include "error.h"

static int lexer_quote_end(t_fragment *fragment, t_quote quote)
{
	if (!str_char_is_quote(*fragment->str))
		return (0);
	if (*fragment->str != quote)
		return (0);
	return (fragment->length % 2);
}

static int	lexer_quote_mark(t_array *fragments, t_quote quote, unsigned long *index)
{
	t_fragment 	*fragment;

	while (*index < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, *index);
		fragment->quote = quote;
		if (lexer_quote_end(fragment, quote))
			return (0);
		(*index)++;
	}
	return (1);
}

static char	*lexer_quote_str(t_quote quote)
{
	if (quote == QUOTE_SINGLE)
		return ("'");
	if (quote == QUOTE_DOUBLE)
		return ("\"");
	return ("");
}

static int	lexer_quote_start(t_fragment *fragment)
{
	t_quote			quote;

	quote = *fragment->str;
	if (!str_char_is_quote(quote))
		return (1);
	fragment->quote = quote;
	return (fragment->length % 2 == 0);
}

int	lexer_quotes_mark(t_array *fragments)
{
	unsigned long	i;
	t_fragment 		*fragment;
	t_quote			quote;

	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		quote = *fragment->str;
		i++;
		if (lexer_quote_start(fragment))
			continue ;
		if (lexer_quote_mark(fragments, quote, &i))
			return (return_syntax(lexer_quote_str(quote)), 1);
		i++;
	}
	return (0);
}
