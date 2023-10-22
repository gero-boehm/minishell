/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:00 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:01 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "global.h"
#include "array.h"

int	mem_free(void *ptr)
{
	if (arr_remove(&global()->allocs, &ptr))
		return (1);
	free(ptr);
	return (0);
}

void	mem_free_from(unsigned long index)
{
	unsigned long	i;
	void			*ptr;

	i = arr_size(&global()->allocs);
	if (index >= i)
		return ;
	while (i-- > index)
	{
		ptr = *(void **) arr_get(&global()->allocs, i);
		free(ptr);
	}
	global()->allocs.size = index;
}

void	mem_free_str_arr(char **arr)
{
	char	**cursor;

	cursor = arr;
	while (*cursor != NULL)
		mem_free(*cursor++);
	mem_free(arr);
}
