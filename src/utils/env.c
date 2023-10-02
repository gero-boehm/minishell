#include <stdlib.h>
#include <limits.h>
#include "global.h"
#include "assoc.h"
#include "str.h"
#include "memory.h"
#include "error.h"

extern char	**environ;

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

static char	*ft_itoa(int n)
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

int	env_init(void)
{
	// TODO: variable export can have mutiple '=' in succession. meaning A==5 with have A as key and =5 as value. make sure splitting the env works correctly in this case
	return (assoc_from_str_arr(&global()->env, environ));
}

int	env_get(const char *key, char **value)
{
	if (str_eq(key, "?"))
	{
		// TODO: write proper conversion function
		*value = ft_itoa(global()->exit_code);
		if (*value == NULL)
			error_fatal();
		return (0);
	}
	return (assoc_get(&global()->env, key, value));
}

int	env_set(const char *key, char *value)
{
	return (assoc_set(&global()->env, key, value));
}

int	env_remove(const char *key)
{
	return (assoc_remove(&global()->env, key));
}

int	env_get_all(char ***arr)
{
	return (assoc_to_str_arr(&global()->env, arr));
}
