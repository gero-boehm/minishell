#include <stdlib.h>
#include "global.h"
#include "assoc.h"
#include "str.h"

extern char	**environ;

int	env_init(void)
{
	// TODO: variable export can have mutiple '=' in succession. meaning A==5 with have A as key and =5 as value. make sure splitting the env works correctly in this case
	return (assoc_from_str_arr(&global()->env, environ));
}

int	env_get(const char *key, char **value)
{
	if (str_eq(key, "?"))
		return (*value = global()->exit_code, 0);
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
