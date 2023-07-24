/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/24 19:55:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"

// int ft_echo(token n, char *str)
void	builtin_echo(int n, char *str)
{
	if (str == NULL)
		str = "";
	printf("%s", str);
	if (!n)
		printf("\n");
}
