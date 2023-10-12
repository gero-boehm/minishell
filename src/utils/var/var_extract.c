#include "array.h"
#include "range.h"
#include "str.h"

static void	vars_var_get_range(const char *str, t_range *var)
{
	const char	*boundaries = " \n\t\r\f\v!\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	char		c;

	var->start += var->length - 1;
	var->length = 1;
	while (1)
	{
		c = str[range_end(var)];
		if (c == '?')
		{
			var->length++;
			return ;
		}
		if (c == '\0' || str_char_in_set(boundaries, c))
			return ;
		var->length++;
	}
}

static int	vars_var_key_extract(const char *str, t_range *var)
{
	t_range	key_range;

	key_range.start = var->start + 1;
	key_range.length = var->length - 1;
	return (str_extract_range(str, &key_range, &var->meta.var_data.key));
}

int	vars_extract(const char *str, unsigned long index, unsigned long offset, t_array *vars)
{
	unsigned long	start;
	t_range			var;

	start = 0;
	var.meta.var_data.index = index;
	while (1)
	{
		if (str_range_of(str, "$", start, &var))
			break ;
		vars_var_get_range(str, &var);
		if (range_length(&var) == 1)
		{
			start = range_end(&var);
			continue ;
		}
		if (vars_var_key_extract(str, &var))
			return (1);
		var.start += offset;
		if (arr_add(vars, &var))
			return (2);
		start = range_end(&var);
	}
	return (0);
}
