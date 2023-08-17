/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:22:10 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 14:13:48 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "globaldef.h"
#include "array.h"
#include "env.h"
#include "cmddef.h"

int	global_init(void)
{
	if (arr_create(&g_global.allocs, sizeof(char *)))
		return (1);
	if (arr_create(&g_global.fds, sizeof(int)))
		return (1);
	if (arr_create(&g_global.heredocs, sizeof(t_heredoc)))
		return (1);
	if (env_init())
		return (2);
	return (0);
}

void	cleanup(void)
{
	size_t	i;
	int		fd;
	void	*ptr;

	i = arr_size(&g_global.fds);
	while (i--)
	{
		fd = *(int *) arr_get(&g_global.fds, i);
		close(fd);
	}
	i = arr_size(&g_global.allocs);
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

void	success(void)
{
	cleanup();
	exit(0);
}
