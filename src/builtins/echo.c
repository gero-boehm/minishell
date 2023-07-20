/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 14:52:54 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"

// int ft_echo(token n, char *str)
int	echo(int n, char *str)
{
	if (str == NULL)
		return (printf("\n"), 1);
	printf("%s", str);
	if (!n)
		printf("\n");
	return (0);
}
