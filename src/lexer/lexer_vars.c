/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:10 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "range.h"
#include "str.h"
#include "vars.h"

int	lexer_vars_get(t_array *fragments, t_array *vars)
{
	unsigned long	i;
	t_fragment		*fragment;
	size_t			length;

	if (arr_create(vars, sizeof(t_range)))
		return (1);
	i = 0;
	length = 0;
	while (i < arr_size(fragments))
	{
		fragment = (t_fragment *) arr_get(fragments, i);
		if (fragment->quote == QUOTE_SINGLE)
		{
			length += fragment->length;
			i++;
			continue ;
		}
		if (vars_extract(fragment->str, 0, length, vars))
			return (2);
		length += fragment->length;
		i++;
	}
	return (0);
}
