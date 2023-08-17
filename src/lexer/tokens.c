/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 01:22:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 14:17:48 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "str.h"
#include "array.h"

static void	lexer_state_init(t_lexer_state *state)
{
	state->mode = MODE_COMMAND;
	state->string_type = STRING_NONE;
	state->is_escaped = 0;
}

static int	lexer_get_command_token(t_array *fragments, t_array *tokens)
{
	unsigned long	i;
	char			*fragment;
	t_token			token;

	fragment = *(char **) arr_get(fragments, 0);
	token.str = fragment;
	i = 1;
	while (i < arr_size(fragments))
	{

	}
}

int	lexer_get_tokens_from_fragments(t_array *fragments, t_array *tokens)
{
	unsigned long	i;
	char			*fragment;
	t_lexer_state	state;

	i = 0;
	while (i < arr_size(fragments))
	{

	}
}