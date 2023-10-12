#include "tokendef.h"
#include "str.h"

int	token_is_operand(t_token *token)
{
	if (token->contained_quotes)
		return (0);
	return (str_char_in_set("&|", *token->str));
}

int	token_is_redirection(t_token *token)
{
	if (token->contained_quotes)
		return (0);
	return (str_char_in_set("<>", *token->str));
}

int	token_is_parenthesis(t_token *token)
{
	if (token->contained_quotes)
		return (0);
	return (str_char_in_set("()", *token->str));
}

int	token_is(t_token *token, t_token_type type)
{
	if (token == NULL)
		return (0);
	return ((token->type & type) == type);
}

int	token_is_any(t_token *token, t_token_type type)
{
	if (token == NULL)
		return (0);
	return ((token->type & type) != 0);
}
