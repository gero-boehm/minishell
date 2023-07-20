/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 14:49:33 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

// str doesn't needs '/' before the dir name for relative but for absolute
int	cd(char *str)
{
	if (str == NULL)
		return (0);
	// TODO: if str is NULL goto home
	if (chdir(str) == -1)
		return (printf("Error\n"), 1);
	return (0);
}
