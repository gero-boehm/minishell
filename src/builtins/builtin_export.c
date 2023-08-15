/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:31:57 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/15 14:05:31 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "global.h"
#include "env.h"
#include "cmddef.h"

void	builtin_export(t_builtin_export	*export)
{
	while (*export->keys != NULL && *export->values != NULL)
	{
		if (env_set(export->keys, export->values))
			error(134);
		*export->keys++;
		*export->values++;
	}
	error(0);
}
