/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:40 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:41 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rangedef.h"

unsigned long	range_start(t_range *range)
{
	return (range->start);
}

unsigned long	range_end(t_range *range)
{
	return (range->start + range->length);
}

size_t	range_length(t_range *range)
{
	return (range->length);
}
