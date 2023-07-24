/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:32:17 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/24 20:01:55 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include "builtins.h"
#include "global.h"

void	builtin_exit(void)
{
	printf("exit\n");
	clear_history();
	error(0);
}
