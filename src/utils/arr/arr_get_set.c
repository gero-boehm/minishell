/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:25:28 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:33:17 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"
#include "memory.h"

void	*arr_get(t_array *arr, unsigned int index)
{
	return (arr->elements + index * arr->bytes);
}

void	arr_set(t_array *arr, unsigned int index, void *element)
{
	void	*ptr;

	ptr = arr->elements + index * arr->bytes;
	mem_ncpy(ptr, element, arr->bytes);
}
