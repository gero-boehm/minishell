/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:51:28 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 18:27:36 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "assoc.h"
#include "array.h"
#include "str.h"

static int	assoc_add(t_assoc *assoc, const char *key, char *value)
{
	if (arr_add(&assoc->keys, &key))
		return (1);
	if (arr_add(&assoc->values, &value))
		return (2);
	return (0);
}

int	assoc_init(t_assoc *assoc)
{
	if (arr_create(&assoc->keys, sizeof(char *)))
		return (1);
	if (arr_create(&assoc->values, sizeof(char *)))
		return (2);
	return (0);
}

int	assoc_set(t_assoc *assoc, const char *key, char *value)
{
	unsigned int	index;

	if (arr_index(&assoc->keys, &key, &index))
		return (assoc_add(assoc, key, value));
	arr_set(&assoc->values, index, &value);
	return (0);
}

int	assoc_get(t_assoc *assoc, const char *key, char **value)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (i < assoc->keys.size)
	{
		tmp = *(char **) arr_get(&assoc->keys, i);
		if (strcmp(tmp, key) == 0)
			break;
		i++;
	}
	*value = *(char **) arr_get(&assoc->values, i);
	return (0);
}

char	*assoc_get_key_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->keys, index));
}

char	*assoc_get_value_at(t_assoc *assoc, unsigned int index)
{
	return (*(char **) arr_get(&assoc->values, index));
}

int	assoc_remove(t_assoc *assoc, const char *key)
{
	unsigned int	index;

	if (arr_index(&assoc->keys, &key, &index))
		return (1);
	if (arr_remove_at(&assoc->keys, index))
		return (2);
	if (arr_remove_at(&assoc->values, index))
		return (2);
	return (0);
}

size_t	assoc_size(t_assoc *assoc)
{
	return (assoc->keys.size);
}

int	assoc_from_str_arr(t_assoc *assoc, char **arr)
{
	char	*key;
	char	*value;

	if (assoc_init(assoc))
		return (1);
	while (*arr != NULL)
	{
		if (str_str_to_exclusive(*arr, "=", 0, &key))
			return (2);
		if (str_str_from_exclusive(*arr, "=", 0, &value))
			return (3);
		if (assoc_set(assoc, key, value))
			return (4);
		arr++;
	}
	return (0);
}

static int	assoc_get_str_at(t_assoc *assoc, unsigned int index, char **str)
{
	char	*cursor;
	char	*key;
	char	*value;
	size_t	len;

	key = assoc_get_key_at(assoc, index);
	value = assoc_get_value_at(assoc, index);
	len = str_len(key) + str_len(value) + 2;
	if (memalloc(len, (void **) str))
		return (1);
	cursor = *str;
	cursor += str_copyn(cursor, key);
	cursor += str_copyn(cursor, "=");
	cursor += str_copyn(cursor, value);
	*cursor = '\0';
	return (0);
}

int	assoc_to_str_arr(t_assoc *assoc, char ***arr)
{
	unsigned long	i;

	if (memalloc((assoc_size(assoc) + 1) * sizeof(char *), (void **) arr))
		return (1);
	i = 0;
	while (i < assoc_size(assoc))
	{
		if (assoc_get_str_at(assoc, i, *arr + i))
			return (2);
		i++;
	}
	(*arr)[i] = NULL;
	return (0);
}

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
