/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:49 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:49 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"
#include "cmddef.h"
#include "error.h"

int	builtin_echo(t_builtin_echo	*echo)
{
	if (echo->str == NULL)
		echo->str = "";
	printf("%s", echo->str);
	if (echo->newline)
		printf("\n");
	return (0);
}
