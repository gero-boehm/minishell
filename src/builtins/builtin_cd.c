/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 18:13:00 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "builtins.h"
#include "global.h"

// str doesn't needs '/' before the dir name for relative but for absolute
void	builtin_cd(char *str)
{
	// TODO: if str is NULL goto home
	// TODO: rebuild chdir for own environment
	if (str == NULL)
		str = "~";
	if (chdir(str) == -1)
		error(ENOENT);
}
