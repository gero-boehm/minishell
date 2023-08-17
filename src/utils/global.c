/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:22:10 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 14:36:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "globaldef.h"
#include "array.h"
#include "env.h"
#include "cmddef.h"

t_global	*global(void)
{
	static t_global global;

	return (&global);
}

int	global_init(void)
{
	if (arr_create(&global()->allocs, sizeof(void *)))
		return (1);
	if (arr_create(&global()->fds, sizeof(int)))
		return (2);
	if (arr_create(&global()->heredocs, sizeof(t_heredoc)))
		return (3);
	if (env_init())
		return (4);
	return (0);
}

void	cleanup(void)
{
	size_t	i;
	int		fd;
	void	*ptr;

	i = arr_size(&global()->fds);
	while (i--)
	{
		fd = *(int *) arr_get(&global()->fds, i);
		close(fd);
	}
	i = arr_size(&global()->allocs);
	while (i--)
	{
		ptr = *(void **) arr_get(&global()->allocs, i);
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
