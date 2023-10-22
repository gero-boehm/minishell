/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:56 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:56 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"
#include "memory.h"

int	arr_clone(t_array *arr, t_array *clone)
{
	if (mem_alloc(arr->max_size * arr->bytes, (void **) &clone->elements))
		return (1);
	mem_ncpy(clone->elements, arr->elements, arr->size * arr->bytes);
	clone->size = arr->size;
	clone->max_size = arr->max_size;
	clone->bytes = arr->bytes;
	return (0);
}
