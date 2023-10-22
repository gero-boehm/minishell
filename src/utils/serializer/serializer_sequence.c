/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:59 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:59 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "serializer.h"
#include "array.h"

int	serializer_serialize_sequence(t_array *sequence, t_array *lines)
{
	unsigned long	i;
	t_chain			*chain;

	i = 0;
	while (i < arr_size(sequence))
	{
		chain = (t_chain *) arr_get(sequence, i);
		if (serializer_serialize_chain(chain, lines))
			return (1);
		i++;
	}
	return (0);
}
