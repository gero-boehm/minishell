/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_serialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:57 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:58 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "serializer.h"
#include "array.h"
#include "str.h"
#include "memory.h"
#include "base64.h"

int	serializer_serialize(t_array *sequence, char **str)
{
	t_array	lines;
	char	*raw;

	if (arr_create(&lines, sizeof(char *)))
		return (1);
	serializer_serialize_sequence(sequence, &lines);
	if (str_from_arr(&lines, "\n", &raw))
		return (2);
	if (base64_encode(raw, str))
		return (3);
	mem_free(raw);
	return (0);
}
