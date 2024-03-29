/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_mask.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:15 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "range.h"
#include "str.h"

static int	lexer_token_mask_value_get(t_fragment *fragment)
{
	if (!str_char_is_whitespace(*fragment->str))
		return (1);
	return (fragment->quote != QUOTE_NONE);
}

static int	lexer_token_mask_spaces(t_array *fragments, t_array *mask)
{
	unsigned long	i;
	t_fragment		*fragment;
	int				value;

	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		value = lexer_token_mask_value_get(fragment);
		if (arr_add(mask, &value))
			return (1);
		i++;
	}
	return (0);
}

static void	lexer_token_mask_operators(t_array *fragments, t_array *mask)
{
	const char		*set = "&|<>()";
	unsigned long	i;
	t_fragment		*fragment;
	static int		counter = 2;

	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		if (fragment->quote != QUOTE_NONE
			|| !str_char_in_set(set, *fragment->str))
		{
			i++;
			continue ;
		}
		arr_set(mask, i, &counter);
		counter++;
		i++;
	}
}

int	lexer_token_mask_get(t_array *fragments, t_array *mask)
{
	if (arr_create(mask, sizeof(int)))
		return (1);
	if (lexer_token_mask_spaces(fragments, mask))
		return (2);
	lexer_token_mask_operators(fragments, mask);
	return (0);
}
