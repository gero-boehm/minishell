/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:01 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:01 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "global.h"

int	set_exit_code(int code)
{
	global()->exit_code = code;
	return (code);
}

void	success(void)
{
	cleanup();
	exit(0);
}

void	error(int code)
{
	cleanup();
	exit(code);
}

void	error_fatal(void)
{
	kill(0, SIGTERM);
}
