/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:57 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:58 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "array.h"
#include "token.h"
#include "parser.h"
#include "global.h"

int	parser_parse(t_array *tokens, t_array *sequence)
{
	unsigned long	index;

	index = 0;
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);
	if (parser_sequence_parse(tokens, &index, sequence))
		return (2);
	return (0);
}
