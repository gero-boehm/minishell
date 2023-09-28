#include "builtins.h"
#include "error.h"
#include "env.h"
#include "cmddef.h"
#include "str.h"

int	builtin_unset(t_builtin_unset *data_unset)
{
	char	**keys;
	int		i;
	char	*set;

	keys = data_unset->keys;
	i = 0;
	if (keys[i][0] == '\0')
		return (1);
	set = " !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	while (keys[i] != NULL)
	{
		if (str_char_in_set(set, *keys[i]))
			return (1);
		if (env_remove(keys[i]))
			return (134);
		i++;
	}
	return (0);
}
