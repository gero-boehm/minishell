/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:33:45 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 18:48:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"

void	arr_free(t_array *arr)
{
	memfree(arr->elements);
	arr->size = 0;
	arr->max_size = 0;
	arr->bytes = 0;
}
