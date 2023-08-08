/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_range3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:21:51 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/06 10:03:31 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

// static void	copy_range(t_range *dst, t_range *src)
// {
// 	dst->start = src->start;
// 	dst->length = src->length;
// }

int	str_range_to_set_exclusive(char *str, char **patterns,
	unsigned long start, t_range *range)
{
	t_range	tmp;
	char	*pattern;
	int		initial;

	initial = 1;
	range->start = start;
	while(*patterns != NULL)
	{
		pattern = *patterns;
		patterns++;
		if(str_range_to_exclusive(str, pattern, start, &tmp))
			continue ;
		if(!initial && tmp.length >= range->length)
			continue;

		initial = 0;
	}
	return (initial);
}

