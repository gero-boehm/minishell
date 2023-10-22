/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command_not_found.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:21 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:21 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"

void	error_command_not_found(char *cmd)
{
	str_print_error(127, cmd, ": command not found", NULL);
	error(127);
}
