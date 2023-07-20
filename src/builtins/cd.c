/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:28:43 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 14:35:27 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// str doesn't needs '/' before the dir name for relative but for absolut
int	cd(char *str)
{
	if (str != NULL)
	{
		if (chdir(str) == -1)
			return (printf("%s\n", "Error"), 1);
		return (0);
	}
	return (1);
}
