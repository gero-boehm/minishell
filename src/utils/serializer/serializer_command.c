/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:03 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "serializer.h"
#include "array.h"

static int	serializer_serialize_command(t_raw_command *command, t_array *lines)
{
	if (append_str("command", lines))
		return (1);
	if (serializer_serialize_args(&command->args, lines))
		return (2);
	if (serializer_serialize_files(&command->files, lines))
		return (3);
	if (serializer_serialize_vars(&command->vars_args, "vars_args", lines))
		return (4);
	if (serializer_serialize_vars(&command->vars_files, "vars_files", lines))
		return (5);
	return (0);
}

int	serializer_serialize_commands(t_array *commands, t_array *lines)
{
	unsigned long	i;
	t_raw_command	*command;

	if (append_str("commands", lines))
		return (1);
	i = 0;
	while (i < arr_size(commands))
	{
		command = (t_raw_command *) arr_get(commands, i);
		if (serializer_serialize_command(command, lines))
			return (2);
		i++;
	}
	return (0);
}
