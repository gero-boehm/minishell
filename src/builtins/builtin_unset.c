/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:30:20 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/16 10:25:05 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
