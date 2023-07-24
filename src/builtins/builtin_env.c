/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:46 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/24 20:01:38 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "global.h"
#include "env.h"
#include "memory.h"

static void	env_print(char **env)
{
	while (*env != NULL)
		printf("%s\n", *env++);
}

void	builtin_env(void)
{
	char	**env;

	if (env_get_all(&env))
		error(134);
	env_print(env);
	mem_free_str_arr(env);
}
