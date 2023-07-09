/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:22:10 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/09 09:40:45 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "globaldef.h"
#include "array.h"
#include "env.h"

int	init_global(void)
{
	if (arr_create(&g_global.allocs, sizeof(void *)))
		return (1);
	if (env_init())
		return (2);
	return (0);
}

void	cleanup(void)
{
	unsigned int	i;
	void			*ptr;

	i = g_global.allocs.size;
	while (i--)
	{
		ptr = *(void **) arr_get(&g_global.allocs, i);
		free(ptr);
	}
}

void	error(int code)
{
	cleanup();
	exit(code);
}
