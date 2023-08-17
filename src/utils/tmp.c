/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:45:42 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/26 13:04:41 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "str.h"

int	tmp_create(int *fd)
{
	char	*random;
	char	*path;

	if (str_random(8, &random))
		return (1);
	if (str_join(&path, "", "/tmp/heredoc_", random, NULL))
		return (2);
	*fd = open(path, O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (*fd == -1)
		return (2);
	return (0);
}

int	tmp_write(int fd, char *str)
{
	size_t	len;

	len = str_len(str);
	return (write(fd, str, len) == -1);
}

void	tmp_close(int fd)
{
	close(fd);
}
