/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_range2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:30 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:30 by cmeng            ###   ########.fr       */
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

int	str_range_of_set(char *str, char *set,
	unsigned long start, t_range *range)
{
	unsigned long	i;
	int				toggle;

	i = start;
	toggle = 0;
	range->length = 0;
	while (1)
	{
		if (str[i] == '\0')
			return (!toggle);
		if (str_char_in_set(set, str[i]))
		{
			if (!toggle)
			{
				range->start = i;
				toggle = 1;
			}
			range->length++;
		}
		else if (toggle)
			return (0);
		i++;
	}
	range->start = i;
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
