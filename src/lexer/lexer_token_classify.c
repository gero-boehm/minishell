#include "token.h"
#include "array.h"

void	lexer_tokens_classify(t_array *tokens)
{
	unsigned long	i;
	t_token			*token;

	i = 0;
	while (i < arr_size(tokens))
	{
		token = (t_token *) arr_get(tokens, i);
		token->type = TOKEN_INVALID;
		if (token_str_is_operand(token->str))
			token_classify_operator(token);
		else if (token_str_is_redirection(token->str))
			token_classify_redirection(token);
		else if (token_str_is_parenthesis(token->str))
			token_classify_parentheses(token);
		else
			token_classify_string(token);
		i++;
	}
}
