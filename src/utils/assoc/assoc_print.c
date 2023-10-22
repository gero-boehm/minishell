/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:34 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:35 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "assocdef.h"
#include "array.h"

void	assoc_print(t_assoc *assoc)
{
	unsigned long	i;
	char			*key;
	char			*value;

	i = 0;
	while (i < assoc->keys.size)
	{
		key = *(char **) arr_get(&assoc->keys, i);
		value = *(char **) arr_get(&assoc->values, i);
		printf("%-20s| %s\n", key, value);
		i++;
	}
}
