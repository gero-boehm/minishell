/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_long_unsafe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:22 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:23 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	str_to_long_unsafe(const char *str, long *num)
{
	int	sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	*num = 0;
	if (*str == '\0')
		return (1);
	while (*str != '\0')
	{
		if (!is_digit(*str))
			return (1);
		*num = *num * 10 + (long)(*str - '0');
		str++;
	}
	*num *= sign;
	return (0);
}
