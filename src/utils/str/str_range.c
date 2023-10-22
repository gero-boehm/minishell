/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_range.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:31 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:32 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	str_range_to_exclusive(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while (str_ncmp(&str[i], pattern, str_len(pattern)))
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	range->start = start;
	range->length = i;
	return (0);
}

int	str_range_to_inclusive(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	if (str_range_to_exclusive(str, pattern, start, range))
		return (1);
	range->length += str_len(pattern);
	return (0);
}

int	str_range_from_inclusive(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while (str_ncmp(&str[i], pattern, str_len(pattern)))
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	range->start = i;
	range->length = str_len(str) - i;
	return (0);
}

int	str_range_from_exclusive(char *str, char *pattern,
	unsigned long start, t_range *range)
{
	size_t	len;

	if (str_range_from_inclusive(str, pattern, start, range))
		return (1);
	len = str_len(pattern);
	range->start += len;
	range->length -= len;
	return (0);
}
