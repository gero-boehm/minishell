/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:37 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:38 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cmddef.h"
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "str.h"

static int	contains_invalid_sign(char *key)
{
	char	*set;

	set = " !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	if (*key == '\0')
		return (1);
	while (*key != '\0')
	{
		if (str_char_in_set(set, *key))
			return (1);
		key++;
	}
	return (0);
}

int	builtin_unset(t_builtin_unset *data_unset)
{
	char	**keys;
	int		i;
	int		has_error;

	keys = data_unset->keys;
	i = 0;
	has_error = 0;
	while (keys[i] != NULL)
	{
		if (contains_invalid_sign(keys[i]))
		{
			return_invalid_identifier("unset", keys[i], NULL);
			has_error = 1;
			i++;
			continue ;
		}
		if (env_remove(keys[i]))
			error_fatal();
		i++;
	}
	return (has_error);
}
