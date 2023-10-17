#include <stdlib.h>
#include "env.h"

char	*path_get_home(void)
{
	char	*home;

	if (env_get("HOME", &home))
		home = getenv("HOME");
	return (home);
}
