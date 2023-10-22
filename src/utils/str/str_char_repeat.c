/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_repeat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:08 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int	str_char_repeat(char c, size_t count, char **str)
{
	unsigned long	i;

	if (mem_alloc_str(count, str))
		return (1);
	i = 0;
	while (i < count)
		(*str)[i++] = c;
	return (0);
}
