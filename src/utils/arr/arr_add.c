/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:26:31 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:33:13 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globaldef.h"
#include "array.h"
#include "memory.h"

static int	arr_grow(t_array *arr)
{
	void			*new;
	unsigned int	index;

	arr->max_size *= 2;
	if (arr_index(&g_global.allocs, &arr->elements, &index))
		return (1);
	if (malloc2(arr->max_size * arr->bytes, (void **) &new))
		return (2);
	arr_set(&g_global.allocs, index, &new);
	mem_ncpy(new, arr->elements, arr->size * arr->bytes);
	free(arr->elements);
	arr->elements = new;
	return (0);
}

int	arr_add(t_array *arr, void *element)
{
	void	*ptr;

	if (arr->size == arr->max_size && arr_grow(arr))
		return (1);
	ptr = arr->elements + arr->size * arr->bytes;
	mem_ncpy(ptr, element, arr->bytes);
	arr->size++;
	return (0);
}
