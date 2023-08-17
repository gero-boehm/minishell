/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/26 16:30:50 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "builtins.h"
#include "global.h"
#include "cmddef.h"

// str doesn't needs '/' before the dir name for relative but for absolute
void	builtin_cd(t_builtin_cd *cd)
{
	// TODO: if str is NULL goto home
	// TODO: rebuild chdir for own environment
	if (cd->path == NULL)
		cd->path = "~";
	if (chdir(cd->path) == -1)
		error(ENOENT);
	error(0);
	// if (str == NULL)
	// 	str = "~";
	// if (chdir(str) == -1)
	// 	error(ENOENT);
}
