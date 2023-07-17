/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:22:55 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:23:35 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"
#include "memory.h"

int	arr_create(t_array *arr, unsigned int bytes)
{
	arr->size = 0;
	arr->max_size = 1;
	arr->bytes = bytes;
	if (memalloc(bytes, &arr->elements))
		return (1);
	return (0);
}