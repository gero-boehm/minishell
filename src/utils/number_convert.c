#include <stdio.h>
#include "memory.h"

static int digit_count(unsigned long num)
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
