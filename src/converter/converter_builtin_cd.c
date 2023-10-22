/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:59 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:50:00 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "str.h"

int	converter_convert_builtin_cd(t_raw_command *raw_command, t_builtin_cd *data)
{
	t_range	range;

	if (arr_size(&raw_command->args) == 1)
		return (str_dup("~", &data->path));
	range.start = 1;
	range.length = 1;
	return (str_from_arr_range(&raw_command->args, &range, "", &data->path));
}
