#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "env.h"

int	vars_expand_str(t_array *vars, char **str)
{
	unsigned long	i;
	t_var			*var;
	char			*value;

	i = arr_size(vars);
	while (i--)
	{
		var = (t_var *) arr_get(vars, i);
		if (env_get(var->key, &value))
			continue ;
		if (str_sub_range(str, &var->range, value))
			return (1);
	}
	return (0);
}

int	vars_expand_str_arr(t_array *vars, char **str)
{
	unsigned long	i;
	t_var			*var;
	char			*value;

	i = arr_size(vars);
	while (i--)
	{
		var = (t_var *) arr_get(vars, i);
		if (env_get(var->key, &value))
			continue ;
		if (str_sub_range(&str[var->index], &var->range, value))
			return (1);
	}
	return (0);
}
