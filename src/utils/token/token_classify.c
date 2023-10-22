/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:30 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:30 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_classify_operator(t_token *token)
{
	token->type |= TOKEN_OPERATOR;
	if (token_classify_operator_and(token))
		return ;
	if (token_classify_operator_or(token))
		return ;
	if (token_classify_operator_pipe(token))
		return ;
	token->type = TOKEN_INVALID;
}

void	token_classify_redirection(t_token *token)
{
	token->type |= TOKEN_REDIRECTION;
	if (token_classify_redirection_in(token))
		return ;
	if (token_classify_redirection_out(token))
		return ;
	if (token_classify_redirection_heredoc(token))
		return ;
	if (token_classify_redirection_append(token))
		return ;
	token->type = TOKEN_INVALID;
}

void	token_classify_parentheses(t_token *token)
{
	token->type |= TOKEN_PARENTHESIS;
	if (token_classify_parenthesis_opening(token))
		return ;
	if (token_classify_parenthesis_closing(token))
		return ;
	token->type = TOKEN_INVALID;
}

void	token_classify_string(t_token *token)
{
	token->type |= TOKEN_STRING;
}
