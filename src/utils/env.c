/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:55:40 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/06 15:07:18 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "assoc.h"

extern char	**environ;

int	env_init(void)
{
	return (assoc_from_str_arr(&global()->env, environ));
}

int	env_get(const char *key, char **value)
{
	return (assoc_get(&global()->env, key, value));
}

int	env_set(const char *key, char *value)
{
	return (assoc_set(&global()->env, key, value));
}

int	env_remove(const char *key)
{
	return (assoc_remove(&global()->env, key));
}

int	env_get_all(char ***arr)
{
	return (assoc_to_str_arr(&global()->env, arr));
}
