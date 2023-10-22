/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_not_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:15 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:16 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"

void	error_not_dir(char *path)
{
	str_print_error(1, "cd: ", path, ": Not a directory", NULL);
	error(1);
}

int	return_not_dir(char *path)
{
	return (str_print_error(1, "cd: ", path, ": Not a directory", NULL));
}
