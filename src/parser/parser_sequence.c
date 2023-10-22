/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:50 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:50 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "global.h"
#include "parser.h"
#include "array.h"
#include "token.h"
#include "error.h"

static int	sequence_end(t_array *tokens, unsigned long index)
{
	t_token	*token;

	if (index >= arr_size(tokens))
		return (1);
	token = (t_token *) arr_get(tokens, index);
	return (token_is(token, TOKEN_CLOSING));
}

int	parser_sequence_parse(
		t_array *tokens, unsigned long *index, t_array *sequence)
{
	t_chain	chain;

	while (1)
	{
		if (parser_chain_parse(tokens, index, &chain))
			return (1);
		if (arr_add(sequence, &chain))
			return (2);
		if (sequence_end(tokens, *index))
			break ;
	}
	return (0);
}
