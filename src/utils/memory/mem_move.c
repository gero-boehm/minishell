/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:17:48 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/09 14:18:12 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*mem_nmov(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	offset;
	size_t	direction;
	size_t	index;

	if (len == 0)
		return (dst);
	if (src == dst)
		return (dst);
	if (src < dst)
		direction = -1;
	else
		direction = 1;
	if (direction == (size_t) -1)
		offset = len - 1;
	else
		offset = 0;
	i = 0;
	while (i < len)
	{
		index = offset + i * direction;
		((char *) dst)[index] = ((char *) src)[index];
		i++;
	}
	return (dst);
}
