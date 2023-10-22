/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classify_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:26 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:26 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokendef.h"
#include "str.h"

int	token_classify_operator_and(t_token *token)
{
	if (!str_eq(token->str, "&&"))
		return (0);
	token->type |= TOKEN_AND;
	return (1);
}

int	token_classify_operator_or(t_token *token)
{
	if (!str_eq(token->str, "||"))
		return (0);
	token->type |= TOKEN_OR;
	return (1);
}

int	token_classify_operator_pipe(t_token *token)
{
	if (!str_eq(token->str, "|"))
		return (0);
	token->type |= TOKEN_PIPE;
	return (1);
}
