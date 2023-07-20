/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:29:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 14:35:57 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// int ft_echo(token n, char *str)
int	echo(int n, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return (1);
	}
	while (str[i + 1] != '\0')
		printf("%c", str[i++]);
	if (!n)
		printf("\n");
	return (0);
}