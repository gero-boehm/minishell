#include <stdlib.h>
#include <limits.h>
#include "global.h"
#include "assoc.h"
#include "str.h"
#include "memory.h"
#include "error.h"
#include "array.h"
#include "number.h"

extern char	**environ;

int	env_init(void)
{
	return (assoc_from_str_arr(&global()->env, environ));
}

int	env_get(const char *key, char **value)
{
	if (str_eq(key, "?"))
	{
		*value = ft_itoa(global()->exit_code);
		if (*value == NULL)
			error_fatal();
		return (0);
	}
	return (assoc_get(&global()->env, key, value));
}

int	env_set(const char *key, char *value)
{
	unsigned long	index;

	if (assoc_set(&global()->env, key, value))
		return (1);
	if (arr_remove(&global()->allocs, &key))
		return (2);
	if (arr_remove(&global()->allocs, &value))
		return (3);
	if (arr_index(&global()->allocs, &global()->exec_path, &index))
		return (0);
	if (arr_insert_at(&global()->allocs, index, &key))
		return (4);
	if (arr_insert_at(&global()->allocs, index, &value))
		return (5);
	return (0);
}

int	env_remove(const char *key)
{
	return (assoc_remove(&global()->env, key));
}

int	env_get_all(char ***arr)
{
	return (assoc_to_str_arr(&global()->env, arr));
}
