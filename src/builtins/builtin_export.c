#include <stdio.h>
#include "builtins.h"
#include "error.h"
#include "env.h"
#include "cmddef.h"
#include "str.h"

int	contains_invalid_sign(char *key)
{
	char	*set;

	set = " !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	while (*key != '\0')
	{
		if (str_char_in_set(set, *key))
			return (1);
		key++;
	}
	return (0);
}

void	builtin_export(t_builtin_export	*data_export)
{
	char	**keys;
	char	**values;
	int		i;

	keys = data_export->keys;
	values = data_export->values;
	i = 0;
	while (keys[i] != NULL)
	{
		if (contains_invalid_sign(keys[i]))
		{
			printf("bash: export: `%s=%s`: not a valid identifier\n", keys[i], values[i]);
			error(1);
		}
		else if (keys[i][0] == '-')
		{
			printf("bash: export: %c%c: invalid option\n", keys[i][0], keys[i][1]);
			printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
			error(1);
		}
		else if (env_set(keys[i], values[i]))
			error(134);
		i++;
	}
	error(0);
}
