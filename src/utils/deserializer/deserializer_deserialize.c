/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserializer_deserialize.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:53:44 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:53:44 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "deserializer.h"
#include "array.h"
#include "str.h"
#include "base64.h"
#include "memory.h"

int	deserializer_deserialize(const char *str, t_array *sequence)
{
	char			*raw;
	unsigned long	index;
	t_array			lines;

	if (base64_decode(str, &raw))
		return (1);
	if (arr_create(&lines, sizeof(char *)))
		return (2);
	if (str_split_all(raw, '\n', &lines))
		return (3);
	index = 0;
	if (deserializer_deserialize_sequence(&lines, &index, sequence))
		return (4);
	mem_free(raw);
	arr_free_ptr(&lines);
	return (0);
}
