/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_numeric_arg_required.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:11 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:14 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"

void	error_numeric_arg_required(char *arg)
{
	str_print_error(255, "exit: ", arg, ": numeric argument required", NULL);
	error(255);
}
