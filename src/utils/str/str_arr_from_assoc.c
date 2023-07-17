/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_from_assoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:14:39 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 18:17:45 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assoc.h"
#include "str.h"

static int	assoc_get_str_at(t_assoc *assoc, unsigned int index, char **str)
{
	char	*cursor;
	char	*key;
	char	*value;
	size_t	len;

	key = assoc_get_key_at(assoc, index);
	value = assoc_get_value_at(assoc, index);
	len = str_len(key) + str_len(value) + 1;
	if (memalloc_str(len, str))
		return (1);
	cursor = *str;
	cursor += str_cpyn(cursor, key);
	cursor += str_cpyn(cursor, "=");
	cursor += str_cpyn(cursor, value);
	return (0);
}

int	assoc_to_str_arr(t_assoc *assoc, char ***arr)
{
	unsigned long	i;

	if (memalloc_str_arr(assoc_size(assoc), arr))
		return (1);
	i = 0;
	while (i < assoc_size(assoc))
	{
		if (assoc_get_str_at(assoc, i, *arr + i))
			return (2);
		i++;
	}
	return (0);
}
