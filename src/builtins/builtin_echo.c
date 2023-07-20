/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 18:12:58 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtins.h"

// int ft_echo(token n, char *str)
void	builtin_echo(int n, char *str)
{
	if (str == NULL)
		return (printf("\n"), 1);
	printf("%s", str);
	if (!n)
		printf("\n");
}
