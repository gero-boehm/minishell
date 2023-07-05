/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:50 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/03 19:09:29 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int	ft_malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src == dst)
		return (dst);
	i = 0;
	while (i < n)
	{
		((char *) dst)[i] = ((char *) src)[i];
		i++;
	}
	return (dst);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*a;
	const unsigned char	*b;

	a = s1;
	b = s2;
	i = 0;
	while (i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}

static int	arr_grow(t_array *arr)
{
	void			*new;
	unsigned int	index;

	arr->max_size *= 2;
	if (arr_index(&g_global.allocs, &arr->elements, &index))
		return (1);
	if (ft_malloc2(arr->max_size * arr->bytes, (void **) &new))
		return (2);
	arr_set(&g_global.allocs, index, &new);
	ft_memcpy(new, arr->elements, arr->size * arr->bytes);
	free(arr->elements);
	arr->elements = new;
	return (0);
}

int	arr_add(t_array *arr, void *element)
{
	void	*ptr;

	if (arr->size == arr->max_size && arr_grow(arr))
		return (1);
	ptr = arr->elements + arr->size * arr->bytes;
	ft_memcpy(ptr, element, arr->bytes);
	arr->size++;
	return (0);
}

void	*arr_get(t_array *arr, unsigned int index)
{
	return (arr->elements + index * arr->bytes);
}

void	arr_set(t_array *arr, unsigned int index, void *element)
{
	void	*ptr;

	ptr = arr->elements + index * arr->bytes;
	ft_memcpy(ptr, element, arr->bytes);
}

int	arr_index(t_array *arr, void *element, unsigned int *index)
{
	unsigned int	i;
	void			*tmp;

	i = 0;
	while (i < arr->size)
	{
		tmp = arr_get(arr, i);
		if(ft_memcmp(tmp, element, arr->bytes) == 0)
		{
			if (index != NULL)
				*index = i;
			return (0);
		}
		i++;
	}
	return (1);
}

int	arr_remove_at(t_array *arr, unsigned int index)
{
	void	*dst;
	void	*src;
	size_t	len;

	dst = arr_get(arr, index);
	src = arr_get(arr, index + 1);
	len = (arr->size - index - 1) * arr->bytes;
	ft_memcpy(dst, src, len);
	arr->size--;
	return (0);
}

int	arr_remove(t_array *arr, void *element)
{
	unsigned int	index;

	if (arr_index(arr, element, &index))
		return (0);
	if (arr_remove_at(arr, index))
		return (1);
	return (0);
}

int	arr_create(t_array *arr, unsigned int bytes)
{
	arr->size = 0;
	arr->max_size = 1;
	arr->bytes = bytes;
	if (memalloc(bytes, &arr->elements))
		return (1);
	return (0);
}

void	arr_free(t_array *arr)
{
	memfree(arr->elements);
	arr->size = 0;
	arr->max_size = 0;
	arr->bytes = 0;
}