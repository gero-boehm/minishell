/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_print_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:34:39 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:34:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "array.h"

void	arr_print_str(t_array *arr)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < arr->size)
	{
		tmp = *(char **) arr_get(arr, i);
		printf("\"%s\"", tmp);
		if (i < arr->size - 1)
			printf(", ");
		i++;
	}
	printf("\n");
}
