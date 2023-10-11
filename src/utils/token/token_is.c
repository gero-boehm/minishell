#include "tokendef.h"
#include "str.h"

int	token_str_is_operand(char *str)
{
	return (str_char_in_set("&|", *str));
}

int	token_str_is_redirection(char *str)
{
	return (str_char_in_set("<>", *str));
}

int	token_str_is_parenthesis(char *str)
{
	return (str_char_in_set("()", *str));
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
