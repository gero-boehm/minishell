/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:31 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:32 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assoc.h"
#include "array.h"

static int	assoc_add(t_assoc *assoc, const char *key, char *value)
{
	if (arr_add(&assoc->keys, &key))
		return (1);
	if (arr_add(&assoc->values, &value))
		return (2);
	return (0);
}

int	assoc_set(t_assoc *assoc, const char *key, char *value)
{
	unsigned long	index;

	if (assoc_index(assoc, key, &index))
		return (assoc_add(assoc, key, value));
	arr_set(&assoc->values, index, &value);
	return (0);
}
