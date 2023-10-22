/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:50:12 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:50:13 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "str.h"

int	converter_convert_builtin_exit(
		t_raw_command *raw_command, t_builtin_exit *data)
{
	t_range	range;

	if (arr_size(&raw_command->args) == 1)
	{
		data->arg = NULL;
		return (0);
	}
	data->too_many_args = arr_size(&raw_command->args) > 2;
	range.start = 1;
	range.length = 1;
	return (str_from_arr_range(&raw_command->args, &range, "", &data->arg));
}
