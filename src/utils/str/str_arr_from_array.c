/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_from_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:13:46 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 15:00:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "array.h"
#include "memory.h"

int	str_arr_from_arr(t_array *arr, char ***strs)
{
	unsigned long	i;
	char			*tmp;

	if (mem_alloc_str_arr(arr->size, strs))
		return (1);
	i = 0;
	while (i < arr_size(arr))
	{
		tmp = *(char **) arr_get(arr, i);
		if (str_dup(tmp, *strs + i))
			return (2);
		i++;
	}
	return (0);
}
