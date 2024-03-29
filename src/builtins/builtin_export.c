/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:42 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:43 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "cmddef.h"
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

int	builtin_export(t_builtin_export	*data_export)
{
	char	**keys;
	char	**values;
	int		i;
	int		has_error;

	keys = data_export->keys;
	values = data_export->values;
	i = 0;
	has_error = 0;
	while (keys[i] != NULL)
	{
		if (contains_invalid_sign(keys[i]))
		{
			return_invalid_identifier("export", keys[i], values[i]);
			has_error = 1;
			i++;
			continue ;
		}
		else if (env_set(keys[i], values[i]))
			error_fatal();
		i++;
	}
	return (has_error);
}
