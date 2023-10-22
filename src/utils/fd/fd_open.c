/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:38 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:39 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "global.h"
#include "error.h"
#include "array.h"

int	fd_open(char *path, int flags, mode_t mode, int *fd)
{
	*fd = open(path, flags, mode);
	if (*fd == -1)
		return (1);
	if (arr_add(&global()->fds, fd))
		error_fatal();
	return (0);
}
