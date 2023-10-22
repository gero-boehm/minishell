/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserializer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:53:39 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:53:40 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "str.h"

int	line_matches(t_array *lines, unsigned long index, const char *match)
{
	char	*line;

	if (index >= arr_size(lines))
		return (0);
	line = *(char **) arr_get(lines, index);
	return (str_eq(line, match));
}
