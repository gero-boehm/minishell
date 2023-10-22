/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:04 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rangedef.h"
#include "str.h"

int	str_contains(char *str, char *match)
{
	t_range	range;

	return (!str_range_of(str, match, 0, &range));
}
