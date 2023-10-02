#include <stdio.h>
#include <limits.h>

int	will_overflow(unsigned long long a, unsigned long long b, size_t size)
{
	if (a + b < a || a - b > a)
		return (1);

	return (0);
	// if (num >> (size * 8 - 1) > 0)
	// 	return (1);
	// return (num * 10 / 10 != num);
}

int	main(void)
{
	// 2147483647
	unsigned long long	a;
	unsigned long long	b;
	int					sign;

	char *str = "5";

	a = 0;
	sign = 0;
	if (*str == '-')
	{
		sign = 1;
		str++;
	}
	else if (*str == '+')
		str++;

	printf("%d\n", ~1 + 1);
	// printf("%lu\n", 21474836474UL >> 31);
	// printf("%d\n", will_overflow(2147483647, sizeof(int)));
	// will_overflow(9223372036854775807, sizeof(long));
	return (0);
}