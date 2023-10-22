/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:59:00 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:59:05 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "memory.h"
#include "str.h"

static int	digit_count(unsigned long num)
{
	int	count;

	count = 1;
	while (num > 9)
	{
		count++;
		num /= 10;
	}
	return (count);
}

static int	get_count(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
			n = INT_MAX;
		else
			n *= -1;
		count++;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	lutoa(unsigned long num, char **str)
{
	int	i;

	i = digit_count(num);
	if (mem_alloc_str(i, str))
		return (1);
	while (i--)
	{
		(*str)[i] = (num % 10) + '0';
		num /= 10;
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	if (n == INT_MIN)
		return (str_dup("-2147483648", &str), str);
	if (n == 0)
		return (str_dup("0", &str), str);
	count = get_count(n);
	if (mem_alloc_str(count, &str))
		return (NULL);
	str[--count] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n)
	{
		str[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
