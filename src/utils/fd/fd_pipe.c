/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:37 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:37 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "global.h"
#include "error.h"
#include "array.h"

int	fd_pipe(int ports[2])
{
	if (pipe(ports) == -1)
		return (1);
	if (arr_add(&global()->fds, &ports[0]))
		return (2);
	if (arr_add(&global()->fds, &ports[1]))
		return (3);
	return (0);
}
