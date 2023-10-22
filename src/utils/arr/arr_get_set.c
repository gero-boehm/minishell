/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:52 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:52 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"
#include "memory.h"

void	*arr_get(t_array *arr, unsigned long index)
{
	return (arr->elements + index * arr->bytes);
}

void	arr_set(t_array *arr, unsigned long index, void *element)
{
	void	*ptr;

	ptr = arr->elements + index * arr->bytes;
	mem_ncpy(ptr, element, arr->bytes);
}
