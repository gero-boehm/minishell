/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:50:09 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:50:10 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "str.h"

int	converter_convert_builtin_unset(
		t_raw_command *raw_command, t_builtin_unset *data)
{
	t_range	range;

	range.start = 1;
	range.length = arr_size(&raw_command->args) - 1;
	return (str_arr_from_arr_range(&raw_command->args, &range, &data->keys));
}
