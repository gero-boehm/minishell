/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_substring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:25 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:26 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	str_str_to_inclusive(char *str, char *pattern,
	unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_to_inclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_to_exclusive(char *str, char *pattern,
	unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_to_exclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_from_inclusive(char *str, char *pattern,
	unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_from_inclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}

int	str_str_from_exclusive(char *str, char *pattern,
	unsigned long start, char **sub)
{
	t_range	range;

	if (str_range_from_exclusive(str, pattern, start, &range))
		return (1);
	return (str_extract_range(str, &range, sub));
}
