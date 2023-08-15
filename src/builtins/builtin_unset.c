/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:30:20 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/15 14:06:46 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "global.h"
#include "env.h"
#include "cmddef.h"

void	builtin_unset(t_builtin_unset *unset)
{
	while (*unset->keys != NULL)
	{
		if (env_remove(unset->keys))
			error(134);
		*unset->values++;
	}
	error(0);
}
