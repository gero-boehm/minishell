/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_not_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:19 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:20 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"

void	error_env_not_set(char *var)
{
	str_print_error(1, "cd: ", var, " not set", NULL);
	error(1);
}

int	return_env_not_set(char *var)
{
	return (str_print_error(1, "cd: ", var, " not set", NULL));
}
