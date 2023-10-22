/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:49 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:49 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "array.h"

static int	get_digit_count(size_t size)
{
	int	count;

	count = 1;
	while (size > 9)
	{
		count++;
		size /= 10;
	}
	return (count);
}

void	arr_print_str(t_array *arr)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	while (i < arr_size(arr))
	{
		tmp = *(char **) arr_get(arr, i);
		printf("\"%s\"", tmp);
		if (i < arr_size(arr) - 1)
			printf(", ");
		i++;
	}
	printf("\n");
}

void	arr_print_ptr(t_array *arr)
{
	unsigned long	i;
	void			*tmp;
	int				padding;

	i = 0;
	padding = get_digit_count(arr_size(arr));
	while (i < arr_size(arr))
	{
		tmp = *(void **) arr_get(arr, i);
		printf("%-*lu: %p\n", padding, i, tmp);
		i++;
	}
}
