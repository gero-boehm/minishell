/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:30 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:35 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "global.h"
#include "error.h"
#include "array.h"

void	fd_close(int fd)
{
	close(fd);
	if (arr_remove(&global()->fds, &fd))
		error_fatal();
}

void	fd_close_all(void)
{
	unsigned long	i;
	int				fd;

	i = 0;
	while (i < arr_size(&global()->fds))
	{
		fd = *(int *) arr_get(&global()->fds, i);
		close(fd);
		i++;
	}
	global()->fds.size = 0;
}
