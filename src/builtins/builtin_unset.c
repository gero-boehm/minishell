#include "builtins.h"
#include "error.h"
#include "env.h"
#include "cmddef.h"

int	builtin_unset(t_builtin_unset *data_unset)
{
	char	**keys;
	int		i;

	keys = data_unset->keys;
	i = 0;
	while (keys[i] != NULL)
	{
		if (env_remove(keys[i]))
			return (134);
		i++;
	}
	return (0);
}
