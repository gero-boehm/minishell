/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:32:17 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 18:12:50 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include "builtins.h"

int	builtin_exit(void)
{
	printf("exit\n");
	clear_history();
	error(0);
}
