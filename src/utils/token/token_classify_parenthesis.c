#include "tokendef.h"
#include "str.h"

int	token_classify_parenthesis_opening(t_token *token)
{
	if (!str_eq(token->str, "("))
		return (0);
	token->type |= TOKEN_OPENING;
	return (1);
}

int	token_classify_parenthesis_closing(t_token *token)
{
	if (!str_eq(token->str, ")"))
		return (0);
	token->type |= TOKEN_CLOSING;
	return (1);
}
