/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/27 05:29:53 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "cmddef.h"
#include "global.h"

void	builtin_echo(t_builtin_echo	*echo)
{
	if (echo->str == NULL)
		echo->str = "";
	printf("%s", echo->str);
	if (echo->newline)
		printf("\n");
	error(0);
}
