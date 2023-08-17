/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_range_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:10:15 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/03 15:32:30 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "memory.h"

int	str_extract_range(char *str, t_range *range, char **sub)
{
	unsigned long	i;

	if (mem_alloc_str(range->length, sub))
		return (1);
	i = 0;
	while (i < range->length)
	{
		(*sub)[i] = str[range->start + i];
		i++;
	}
	return (0);
}

int	str_sub_range(char **str, t_range *range, char *sub)
{
	t_range	range_head;
	t_range	range_tail;
	char	*head;
	char	*tail;
	char	*new;

	range_head.start = 0;
	range_head.length = range->start;
	range_tail.start = range->start + range->length;
	range_tail.length = str_len(*str) - range_tail.start;
	if (str_extract_range(*str, &range_head, &head))
		return (1);
	if (str_extract_range(*str, &range_tail, &tail))
		return (2);
	if (str_join(&new, "", head, sub, tail, NULL))
		return (3);
	mem_free(head);
	mem_free(tail);
	mem_free(*str);
	*str = new;
	return (0);
}

int	str_cut_range(char **str, t_range *range)
{
	return (str_sub_range(str, range, ""));
}
