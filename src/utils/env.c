/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:47 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:48 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "global.h"
#include "assoc.h"
#include "str.h"
#include "memory.h"
#include "error.h"
#include "array.h"
#include "number.h"

extern char	**environ;

int	env_init(void)
{
	return (assoc_from_str_arr(&global()->env, environ));
}

int	env_get(const char *key, char **value)
{
	if (str_eq(key, "?"))
	{
		*value = ft_itoa(global()->exit_code);
		if (*value == NULL)
			error_fatal();
		return (0);
	}
	return (assoc_get(&global()->env, key, value));
}

int	env_set(const char *key, char *value)
{
	if (assoc_set(&global()->env, key, value))
		return (1);
	return (0);
}

int	env_remove(const char *key)
{
	return (assoc_remove(&global()->env, key));
}

int	env_get_all(char ***arr)
{
	return (assoc_to_str_arr(&global()->env, arr));
}
