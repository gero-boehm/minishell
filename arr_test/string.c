/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:44:35 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/05 13:27:23 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "array.h"

int	str_range_to(char *str, char *pattern, unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while (strncmp(&str[i], pattern, strlen(pattern)))
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	range->start = start;
	range->length = i;
	return (0);
}

int	str_range_of(char *str, char *pattern, unsigned long start, t_range *range)
{
	size_t	i;

	i = start;
	while (strncmp(&str[i], pattern, strlen(pattern)))
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	range->start = i;
	range->length = strlen(pattern);
	return (0);
}

static int	str_char_in_set(char *set, char c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

// int	str_range_of_set(char *str, char *set, unsigned long start, t_range *range)
// {
// 	size_t	i;

// 	i = start;
// 	while (strncmp(&haystack[i], needle, strlen(needle)))
// 	{
// 		if (haystack[i] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	range->start = i;
// 	range->length = strlen(needle);
// 	return (0);
// }

int	str_trim_start(char **str, char *set)
{
	t_range	range;
	char	c;
	char	*trimmed;

	range.start = 0;
	while (1)
	{
		c = (*str)[range.start];
		if (c == '\0' || !str_char_in_set(set, c))
			break ;
		range.start++;
	}
	range.length = strlen(*str) - range.start;
	if (str_extract_range(*str, &range, &trimmed))
		return (1);
	memfree(*str);
	*str = trimmed;
	return (0);
}

int	str_trim_end(char **str, char *set)
{
	t_range	range;
	char	c;
	char	*trimmed;

	range.start = 0;
	range.length = strlen(*str);
	while (range.length > 0)
	{
		c = (*str)[range.length - 1];
		if (!str_char_in_set(set, c))
			break ;
		range.length--;
	}
	if (str_extract_range(*str, &range, &trimmed))
		return (1);
	memfree(*str);
	*str = trimmed;
	return (0);
}

int	str_trim(char **str, char *set)
{
	return (str_trim_start(str, set) || str_trim_end(str, set));
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