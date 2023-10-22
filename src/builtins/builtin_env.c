/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:46 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:47 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "memory.h"

static void	env_print(char **env)
{
	while (*env != NULL)
		printf("%s\n", *env++);
}

int	builtin_env(void)
{
	char	**env;

	if (env_get_all(&env))
		error_fatal();
	env_print(env);
	mem_free_str_arr(env);
	return (0);
}
