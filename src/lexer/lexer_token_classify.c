/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_classify.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:16 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:17 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (token_is_operand(token))
			token_classify_operator(token);
		else if (token_is_redirection(token))
			token_classify_redirection(token);
		else if (token_is_parenthesis(token))
			token_classify_parentheses(token);
		else
			token_classify_string(token);
		i++;
	}
}
