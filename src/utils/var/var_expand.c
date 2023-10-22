/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:39 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:39 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rangedef.h"
#include "array.h"
#include "env.h"
#include "str.h"
#include "error.h"

static int	vars_get_value(const char *key, char **value)
{
	if (env_get(key, value))
		return (str_dup("", value));
	return (0);
}

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
		if (vars_get_value(var->meta.var_data.key, &value))
			return (1);
		if (str_sub_range(str, var, value))
			return (2);
	}
	return (0);
}

int	vars_expand_str_split(
		char *str, t_array *vars, unsigned long index, t_array *parts)
{
	unsigned long	i;
	t_range			*var;
	char			*value;
	int				no_vars;

	no_vars = 1;
	i = arr_size(vars);
	while (i--)
	{
		var = (t_range *) arr_get(vars, i);
		if (var->meta.var_data.index != index)
			continue ;
		if (vars_get_value(var->meta.var_data.key, &value))
			error_fatal();
		str_char_replace(value, ' ', '\x01');
		if (str_sub_range(&str, var, value))
			error_fatal();
		no_vars = 0;
	}
	if (no_vars)
		return (1);
	if (str_split(str, '\x01', parts))
		error_fatal();
	return (0);
}
