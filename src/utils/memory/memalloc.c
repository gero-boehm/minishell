/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:45:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:18:44 by gbohm            ###   ########.fr       */
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

int	memalloc(size_t count, void **ptr)
{
	if (malloc2(count, ptr))
		return (1);
	if (arr_add(&g_global.allocs, ptr))
		return (2);
	return (0);
}

int	memfree(void *ptr)
{
	if (arr_remove(&g_global.allocs, &ptr))
		return (1);
	free(ptr);
	return (0);
}

int	memalloc_str_arr(size_t	count, char ***arr)
{
	size_t	bytes;

	bytes = (count + 1) * sizeof(char *);
	if (memalloc(bytes, (void **) arr))
		return (1);
	(*arr)[count] = NULL;
	return (0);
}

int	memalloc_str(size_t	count, char **str)
{
	size_t	bytes;

	bytes = count + 1;
	if (memalloc(bytes, (void **) str))
		return (1);
	(*str)[count] = '\0';
	return (0);
}