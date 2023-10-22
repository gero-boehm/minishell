/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classify_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:31 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:31 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokendef.h"
#include "str.h"

int	token_classify_redirection_in(t_token *token)
{
	if (!str_eq(token->str, "<"))
		return (0);
	token->type |= TOKEN_IN;
	return (1);
}

int	token_classify_redirection_out(t_token *token)
{
	if (!str_eq(token->str, ">"))
		return (0);
	token->type |= TOKEN_OUT;
	return (1);
}

int	token_classify_redirection_heredoc(t_token *token)
{
	if (!str_eq(token->str, "<<"))
		return (0);
	token->type |= TOKEN_HEREDOC;
	return (1);
}

int	token_classify_redirection_append(t_token *token)
{
	if (!str_eq(token->str, ">>"))
		return (0);
	token->type |= TOKEN_APPEND;
	return (1);
}
