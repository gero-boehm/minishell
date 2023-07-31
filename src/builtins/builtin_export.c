/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:31:57 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/26 16:28:31 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "global.h"
#include "env.h"
#include "cmddef.h"

void	builtin_export(t_builtin_export	*export)
{
	if (env_set(export->key, export->value))
		error(134);
	error(0);
}
