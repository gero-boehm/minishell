/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:33:45 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 15:00:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"

void	arr_free(t_array *arr)
{
	mem_free(arr->elements);
	arr->size = 0;
	arr->max_size = 0;
	arr->bytes = 0;
}
