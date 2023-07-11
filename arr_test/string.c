/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:44:35 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/11 17:06:49 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdarg.h>
#include "array.h"
#include "str.h"
#include "memory.h"

int	str_range_to_exclusive(char *str, char *pattern, unsigned long start, t_range *range)
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

int	str_range_to_inclusive(char *str, char *pattern, unsigned long start, t_range *range)
{
	if (str_range_to_exclusive(str, pattern, start, range))
		return (1);
	range->length += str_len(pattern);
	return (0);
}

int	str_range_from_inclusive(char *str, char *pattern, unsigned long start, t_range *range)
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

int	str_range_from_exclusive(char *str, char *pattern, unsigned long start, t_range *range)
{
	size_t	len;

	if (str_range_from_inclusive(str, pattern, start, range))
		return (1);
	len = str_len(pattern);
	range->start += len;
	range->length -= len;
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

int	str_range_of(char *str, char *pattern, unsigned long start, t_range *range)
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

int	str_range_between(char *str, char *pattern, unsigned long start, t_range *range)
{
	if (str_range_from_exclusive(str, pattern, start, range))
		return (1);
	if (str_range_to_exclusive(str, pattern, range->start, range))
		return (2);
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

size_t	str_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	str_cpyn(char *dst, const char *src)
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

int	str_ncmp(const char *s1, const char *s2, size_t n)
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
	return (str_ncmp(s1, s2, str_len(s2)));
}

int	str_eq(const char *s1, const char *s2)
{
	return (str_cmp(s1, s2) == 0);
}

int	str_dup(const char *str, char **dup)
{
	size_t	len;

	len = str_len(str);
	if (memalloc(len + 1, (void **) dup))
		return (1);
	str_cpyn(*dup, str);
	(*dup)[len] = '\0';
	return (0);
}

int	str_join(char **str, const char *sep, ...)
{
	va_list	args;
	t_array	parts;
	char	*part;

	if (arr_create(&parts, sizeof(char *)))
		return (1);
	va_start(args, sep);
	while (1)
	{
		part = va_arg(args, char *);
		if (part == NULL)
			break ;
		if (arr_size(&parts) > 0 && arr_add(&parts, &sep))
			return (va_end(args), 2);
		if (arr_add(&parts, &part))
			return (va_end(args), 3);
	}
	va_end(args);
	if (arr_to_str(&parts, str))
		return (4);
	arr_free(&parts);
	return (0);
}

// int	str_range_of_set(char *str, char *set, unsigned long start, t_range *range)
// {
// 	size_t	i;

// 	i = start;
// 	while (str_ncmp(&haystack[i], needle, str_len(needle)))
// 	{
// 		if (haystack[i] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	range->start = i;
// 	range->length = str_len(needle);
// 	return (0);
// }

int	str_cut_start(char **str, char *cut)
{
	t_range			range;
	char			*new;
	unsigned long	len;

	len = str_len(cut);
	if (str_ncmp(*str, cut, len))
		return (0);
	range.start = 0;
	range.length = len;
	if (str_cut_range(*str, &range, &new))
		return (1);
	memfree(*str);
	*str = new;
	return (0);
}

int	str_cut_end(char **str, char *cut)
{
	t_range			range;
	char			*new;
	unsigned long	len;
	unsigned long	start;

	len = str_len(cut);
	start = str_len(*str) - len;
	if (str_ncmp(*str + start, cut, len))
		return (0);
	range.start = start;
	range.length = len;
	if (str_cut_range(*str, &range, &new))
		return (1);
	memfree(*str);
	*str = new;
	return (0);
}

int	str_cut(char **str, char *cut)
{
	t_range			range;
	char			*new;

	while (1)
	{
		if (str_range_of(*str, cut, 0, &range))
			return (0);
		if (str_cut_range(*str, &range, &new))
			return (1);
		memfree(*str);
		*str = new;
	}
	return (0);
}

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
	range.length = str_len(*str) - range.start;
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
	range.length = str_len(*str);
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

	if (str_memalloc(range->length, sub))
		return (1);
	i = 0;
	while (i < range->length)
	{
		(*sub)[i] = str[range->start + i];
		i++;
	}
	return (0);
}

int	str_cut_range(char *str, t_range *range, char **sub)
{
	t_range	range_head;
	t_range	range_tail;
	char	*head;
	char	*tail;

	range_head.start = 0;
	range_head.length = range->start;
	range_tail.start = range->start + range->length;
	range_tail.length = str_len(str) - range_tail.start;
	if (str_extract_range(str, &range_head, &head))
		return (1);
	if (str_extract_range(str, &range_tail, &tail))
		return (2);
	if (str_join(sub, "", head, tail, NULL))
		return (3);
	memfree(head);
	memfree(tail);
	return (0);
}

int	str_memalloc_arr(size_t	count, char ***arr)
{
	size_t	bytes;

	bytes = (count + 1) * sizeof(char *);
	if (memalloc(bytes, (void **) arr))
		return (1);
	(*arr)[count] = NULL;
	return (0);
}

int	str_memalloc(size_t	count, char **str)
{
	size_t	bytes;

	bytes = count + 1;
	if (memalloc(bytes, (void **) str))
		return (1);
	(*str)[count] = '\0';
	return (0);
}
