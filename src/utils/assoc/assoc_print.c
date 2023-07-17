/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:21:03 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 18:48:44 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "assocdef.h"
#include "array.h"

void	assoc_print(t_assoc *assoc)
{
	unsigned int	i;
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
