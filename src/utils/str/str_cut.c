/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:58:38 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 15:00:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "memory.h"

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
	mem_free(*str);
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
	mem_free(*str);
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
		mem_free(*str);
		*str = new;
	}
	return (0);
}
