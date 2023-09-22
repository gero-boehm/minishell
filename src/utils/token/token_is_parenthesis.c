#include "tokendef.h"
#include "str.h"

int token_is_parenthesis_opening(t_token *token)
{
	return (str_eq(token->str, "("));
}

int token_is_parenthesis_closing(t_token *token)
{
	return (str_eq(token->str, ")"));
}

int token_is_possibly_parenthesis(t_token *token)
{
	char	c;

	c = *token->str;
	return (c == '(' || c == ')');
}
