/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:21 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:21 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "memory.h"

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
	mem_free(*str);
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
	mem_free(*str);
	*str = trimmed;
	return (0);
}

int	str_trim(char **str, char *set)
{
	return (str_trim_start(str, set) || str_trim_end(str, set));
}
