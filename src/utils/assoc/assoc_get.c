/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:37 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:37 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assoc.h"
#include "array.h"
#include "str.h"

char	*assoc_get_key_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->keys, index));
}

char	*assoc_get_value_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->values, index));
}

int	assoc_get(t_assoc *assoc, const char *key, char **value)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < assoc_size(assoc))
	{
		tmp = assoc_get_key_at(assoc, i);
		if (str_eq(tmp, key))
		{
			if (value != NULL)
				*value = assoc_get_value_at(assoc, i);
			return (0);
		}
		i++;
	}
	if (value != NULL)
		*value = NULL;
	return (1);
}
