#include "tokendef.h"

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
