/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:11 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:12 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "array.h"
#include "error.h"

static int	lexer_token_invalid_op_or_redir(t_token *current, t_token *last)
{
	if ((last == NULL || token_is(last, TOKEN_OPENING))
		&& token_is(current, TOKEN_OPERATOR))
		return (1);
	if (token_is_any(last, TOKEN_OPERATOR | TOKEN_REDIRECTION)
		&& token_is(current, TOKEN_OPERATOR))
		return (1);
	return (0);
}

static int	lexer_token_invalid_opening_parenthesis(t_token *current,
	t_token *last)
{
	if (last == NULL)
		return (0);
	if (token_is_any(last, TOKEN_OPERATOR | TOKEN_OPENING))
		return (0);
	return (token_is(current, TOKEN_OPENING));
}

static int	lexer_token_invalid_closing_parenthesis(t_token *current,
	t_token *last)
{
	if (token_is(last, TOKEN_CLOSING)
		&& !token_is_any(current, TOKEN_OPERATOR | TOKEN_CLOSING))
		return (1);
	if (!token_is(current, TOKEN_CLOSING))
		return (0);
	if (last == NULL)
		return (1);
	return (token_is_any(last, TOKEN_OPERATOR | TOKEN_REDIRECTION
			| TOKEN_OPENING));
}

static int	lexer_token_subshell_depth(t_token *current, int *depth)
{
	if (token_is(current, TOKEN_OPENING))
		*depth += (int) current->length;
	if (token_is(current, TOKEN_CLOSING))
		*depth -= (int) current->length;
	return (*depth < 0);
}

int	lexer_tokens_validate(t_array *tokens)
{
	unsigned long	i;
	t_token			*current;
	t_token			*last;
	int				depth;

	i = 0;
	last = NULL;
	depth = 0;
	while (i < arr_size(tokens))
	{
		current = (t_token *) arr_get(tokens, i++);
		if (current->type == TOKEN_INVALID
			|| lexer_token_invalid_op_or_redir(current, last)
			|| lexer_token_invalid_opening_parenthesis(current, last)
			|| lexer_token_invalid_closing_parenthesis(current, last)
			|| lexer_token_subshell_depth(current, &depth))
			return (return_syntax(current->str), 1);
		if (i == arr_size(tokens)
			&& token_is_any(current, TOKEN_OPERATOR | TOKEN_REDIRECTION))
			return (return_syntax("newline"), 1);
		last = current;
	}
	if (depth > 0)
		return (return_syntax("("), 6);
	return (0);
}
