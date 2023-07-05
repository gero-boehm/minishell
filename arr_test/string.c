/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:44:35 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/05 10:56:54 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "array.h"

int	str_range_to(char *haystack, char *needle, unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while(strncmp(&haystack[i], needle, strlen(needle)))
	{
		if (haystack[i] == '\0')
			return (1);
		i++;
	}
	range->start = start;
	range->length = i;
	return (0);
}

int	str_range_of(char *haystack, char *needle, unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while(strncmp(&haystack[i], needle, strlen(needle)))
	{
		if (haystack[i] == '\0')
			return (1);
		i++;
	}
	range->start = start;
	range->length = i;
	return (0);
}

int	str_extract_range(char *str, t_range *range, char **sub)
{
	unsigned long	i;

	if (memalloc(range->length + 1, (void **) sub))
		return (1);
	i = 0;
	while (i < range->length)
	{
		(*sub)[i] = str[range->start + i];
		i++;
	}
	(*sub)[i] = 0;
	return (0);
}