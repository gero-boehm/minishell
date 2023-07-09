/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:44:35 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/09 08:14:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "array.h"
#include "str.h"
#include "memory.h"

int	str_range_to_exclusive(char *str, char *pattern, unsigned long start, t_range *range)
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

int	str_range_to_inclusive(char *str, char *pattern, unsigned long start, t_range *range)
{
	if (str_range_to_exclusive(str, pattern, start, range))
		return (1);
	range->length += strlen(pattern);
	return (0);
}

int	str_range_from_inclusive(char *str, char *pattern, unsigned long start, t_range *range)
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
	range->length = strlen(str) - i;
	return (0);
}

int	str_range_from_exclusive(char *str, char *pattern, unsigned long start, t_range *range)
{
	size_t	len;

	if (str_range_from_inclusive(str, pattern, start, range))
		return (1);
	len = strlen(pattern);
	range->start += len;
	range->length -= len;
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

int	str_str_to_inclusive(char *str, char *pattern, unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_to_inclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_to_exclusive(char *str, char *pattern, unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_to_exclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_from_inclusive(char *str, char *pattern, unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_from_inclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_from_exclusive(char *str, char *pattern, unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_from_exclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
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

size_t	str_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	str_copyn(char *dst, const char *src)
{
	unsigned long	i;
	size_t			len;

	i = 0;
	len = str_len(src);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (len);
}

int	str_cmpn(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*a;
	const unsigned char	*b;

	i = 0;
	a = (const unsigned char *) s1;
	b = (const unsigned char *) s2;
	while (i < n)
	{
		if (!a[i] || !b[i] || a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}

int	str_cmp(const char *s1, const char *s2)
{
	return (str_cmpn(s1, s2, str_len(s2)));
}

int	str_eq(const char *s1, const char *s2)
{
	return (str_cmp(s1, s2) == 0);
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