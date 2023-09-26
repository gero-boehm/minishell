#include "cmddef.h"
#include "array.h"
#include "range.h"
#include "str.h"
#include "env.h"

int	vars_expand_str(t_array *vars, unsigned long index, char **str)
{
	unsigned long	i;
	t_range			*var;
	char			*value;

	i = arr_size(vars);
	while (i--)
	{
		var = (t_range *) arr_get(vars, i);
		if (var->meta.var_data.index != index)
			continue ;
		if (env_get(var->meta.var_data.key, &value))
			continue ;
		if (str_sub_range(str, var, value))
			return (1);
	}
	return (0);
}

int	vars_expand_str_arr(t_array *vars, char **str)
{
	unsigned long	i;
	t_range			*var;
	char			*value;

	i = arr_size(vars);
	while (i--)
	{
		var = (t_range *) arr_get(vars, i);
		if (env_get(var->meta.var_data.key, &value))
			continue ;
		if (str_sub_range(&str[var->meta.var_data.index], var, value))
			return (1);
	}
	return (0);
}
