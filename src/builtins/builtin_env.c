#include <stdio.h>
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "memory.h"

static void	env_print(char **env)
{
	while (*env != NULL)
		printf("%s\n", *env++);
}

int	builtin_env(void)
{
	char	**env;

	if (env_get_all(&env))
		return(134);
	env_print(env);
	mem_free_str_arr(env);
	return(0);
}
