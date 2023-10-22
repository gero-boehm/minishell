/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:50:04 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:50:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "array.h"
#include "str.h"

int	converter_convert_external(t_raw_command *raw_command, t_external *data)
{
	return (str_arr_from_arr(&raw_command->args, &data->args));
}
