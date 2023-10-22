/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:28 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:28 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"

char	*path_get_home(void)
{
	char	*home;

	if (env_get("HOME", &home))
		home = getenv("HOME");
	return (home);
}
