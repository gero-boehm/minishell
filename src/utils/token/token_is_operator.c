#include "tokendef.h"
#include "str.h"

int	token_is_and(t_token *token)
{
	return (str_eq(token->str, "&&"));
}

int	token_is_or(t_token *token)
{
	return (str_eq(token->str, "||"));
}

int	token_is_pipe(t_token *token)
{
	return (str_eq(token->str, "|"));
}

int token_is_operator(t_token *token)
{
	return (
		token_is_and(token) ||
		token_is_or(token) ||
		token_is_pipe(token)
	);
}