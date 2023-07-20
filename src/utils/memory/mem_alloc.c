/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:45:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 14:57:34 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "globaldef.h"
#include "array.h"

int	malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

int	mem_add(void *ptr)
{
	return (arr_add(&g_global.allocs, &ptr));
}

int	mem_alloc(size_t count, void **ptr)
{
	if (malloc2(count, ptr))
		return (1);
	if (mem_add(*ptr))
		return (2);
	return (0);
}

int	mem_free(void *ptr)
{
	if (arr_remove(&g_global.allocs, &ptr))
		return (1);
	free(ptr);
	return (0);
}
