#include "tokendef.h"
#include "rangedef.h"
#include "array.h"
#include "error.h"

void	parser_vars_copy(t_token *token, unsigned long index, t_array *vars)
{
	unsigned long	i;
	t_range			*var;

	i = 0;
	while (i < arr_size(&token->vars))
	{
		var = (t_range *) arr_get(&token->vars, i);
		var->meta.var_data.index = index;
		if (arr_add(vars, var))
			error_fatal();
		i++;
	}
}