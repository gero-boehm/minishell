/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_range2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:56:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 13:56:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	str_range_of(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	unsigned long	i;
	size_t			len;

	i = start;
	len = str_len(pattern);
	while (str_ncmp(&str[i], pattern, len))
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	range->start = i;
	range->length = len;
	return (0);
}

int	str_range_between(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	if (str_range_from_exclusive(str, pattern, start, range))
		return (1);
	if (str_range_to_exclusive(str, pattern, range->start, range))
		return (2);
	return (0);
}
