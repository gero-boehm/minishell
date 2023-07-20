/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free_str_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:56:16 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 17:57:55 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	mem_free_str_arr(char **arr)
{
	char	**cursor;

	cursor = arr;
	while (*cursor != NULL)
		mem_free(*cursor++);
	mem_free(arr);
}
