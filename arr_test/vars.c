/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:30:13 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/03 18:57:45 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "array.h"

int	vars_init(void)
{
	if(arr_create(&g_global.vars.keys, sizeof(char *)))
		return (1);
	if(arr_create(&g_global.vars.values, sizeof(char *)))
		return (2);
	return (0);
}

static int	var_add(char *key, char *value)
{
	if (arr_add(&g_global.vars.keys, &key))
		return (1);
	if (arr_add(&g_global.vars.values, &value))
		return (2);
	return (0);
}

int	var_set(char *key, char *value)
{
	unsigned int	index;

	if(arr_index(&g_global.vars.keys, &key, &index))
		return (var_add(key, value));
	arr_set(&g_global.vars.values, index, &value);
	return (0);
}

int	var_get(char *key, char **value)
{
	unsigned int	index;

	if(arr_index(&g_global.vars.keys, &key, &index))
		return (1);
	*value = *(char **) arr_get(&g_global.vars.values, index);
	return (0);
}

void	vars_print(void)
{
	unsigned int	i;
	char			*key;
	char			*value;

	i = 0;
	printf("---------------------\n");
	while(i < g_global.vars.keys.size)
	{
		key = *(char **) arr_get(&g_global.vars.keys, i);
		value = *(char **) arr_get(&g_global.vars.values, i);

		printf("%-10s| %s\n", key, value);
		i++;
	}
	printf("---------------------\n");
}
