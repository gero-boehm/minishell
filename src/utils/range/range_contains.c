/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_contains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:37 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:38 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "range.h"

int	range_contains(t_range *range, unsigned long index)
{
	return (range_start(range) <= index && range_end(range) > index);
}

int	range_contains_range(t_range *outside, t_range *inside)
{
	if (range_start(inside) < range_start(outside))
		return (0);
	if (range_end(inside) > range_end(outside))
		return (0);
	return (1);
}
