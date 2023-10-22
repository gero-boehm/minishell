/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_segments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:25 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:25 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "array.h"
#include "str.h"

static int	path_clone_segments(t_array *segments, t_array *clone)
{
	unsigned long	i;
	char			*segment;

	if (arr_create(clone, segments->bytes))
		return (1);
	i = 0;
	while (i < arr_size(segments))
	{
		segment = *(char **) arr_get(segments, i);
		if (str_dup(segment, &segment))
			return (2);
		if (arr_add(clone, &segment))
			return (3);
		i++;
	}
	return (0);
}

int	path_get_updated_segments(t_array *segments, t_array *clone,
	char *name, unsigned long index)
{
	if (path_clone_segments(segments, clone))
		return (1);
	if (str_dup(name, &name))
		return (2);
	arr_set(clone, index, &name);
	return (0);
}

int	path_get_segments(char *str, t_array *segments)
{
	t_array	boundaries;

	if (arr_create(segments, sizeof(char *)))
		return (1);
	if (path_get_pattern_boundaries(str, &boundaries))
		return (2);
	if (arr_size(&boundaries) == 1)
		return (arr_add(segments, &str));
	if (path_get_segments_from_boundaries(str, &boundaries, segments))
		return (4);
	arr_free(&boundaries);
	return (0);
}
