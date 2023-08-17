#include "builtins.h"
#include "global.h"
#include "env.h"
#include "cmddef.h"

void	builtin_unset(t_builtin_unset *data_unset)
{
	char	**keys;
	int		i;

	keys = data_unset->keys;
	i = 0;
	while (keys[i] != NULL)
	{
		if (env_remove(keys[i]))
			error(134);
		i++;
	}
	error(0);
}
