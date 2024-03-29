/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:33 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:33 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assoc.h"
#include "array.h"

int	assoc_remove(t_assoc *assoc, const char *key)
{
	unsigned long	index;

	if (assoc_index(assoc, key, &index))
		return (0);
	if (arr_remove_at(&assoc->keys, index))
		return (1);
	if (arr_remove_at(&assoc->values, index))
		return (2);
	return (0);
}
