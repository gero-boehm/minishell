/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:54 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:54 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"
#include "array.h"

static int	serializer_serialize_arg(char *arg, t_array *lines)
{
	if (append_str("arg", lines))
		return (1);
	if (arr_add(lines, &arg))
		return (2);
	return (0);
}

int	serializer_serialize_args(t_array *args, t_array *lines)
{
	unsigned long	i;
	char			*arg;

	if (append_str("args", lines))
		return (1);
	i = 0;
	while (i < arr_size(args))
	{
		arg = *(char **) arr_get(args, i);
		if (serializer_serialize_arg(arg, lines))
			return (2);
		i++;
	}
	return (0);
}
