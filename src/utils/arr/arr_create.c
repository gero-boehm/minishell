/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:55 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:55 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"
#include "memory.h"

int	arr_create(t_array *arr, unsigned int bytes)
{
	arr->size = 0;
	arr->max_size = 1;
	arr->bytes = bytes;
	if (mem_alloc(bytes, &arr->elements))
		return (1);
	return (0);
}
