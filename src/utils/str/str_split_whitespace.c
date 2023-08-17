/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_whitespace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:47:42 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/06 09:49:52 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "array.h"

static int	is_escaped(char *str, unsigned long index)
{
	int	backslashes;

	if (index == 0)
		return (0);
	backslashes = 0;
	while (index > 0)
	{
		index--;
		if (str[index] != '\\')
			break;
		backslashes++;
	}
	return (backslashes % 2);
}

int	is_whitespace(char c)
{
	const char	*set = " \n\t\r\f\v";
	return (str_char_in_set(set, c));
}

int	str_to_segments(char *str, t_array *segments)
{
	char	quote;

	if (arr_create(segments, sizeof(char *)))
		return (1);
	quote = 0;

}


