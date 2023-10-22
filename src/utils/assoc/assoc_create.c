/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:52:28 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:52:40 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assoc.h"
#include "array.h"
#include "str.h"

int	assoc_create(t_assoc *assoc)
{
	if (arr_create(&assoc->keys, sizeof(char *)))
		return (1);
	if (arr_create(&assoc->values, sizeof(char *)))
		return (2);
	return (0);
}

int	assoc_from_str_arr(t_assoc *assoc, char **arr)
{
	char	*key;
	char	*value;

	if (assoc_create(assoc))
		return (1);
	while (*arr != NULL)
	{
		if (str_key_value(*arr, &key, &value))
			return (2);
		if (assoc_set(assoc, key, value))
			return (3);
		arr++;
	}
	return (0);
}
