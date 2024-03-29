/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_no_file_or_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:17 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:17 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"

// TODO: find out where this is used and if only in cd, add "cd:" to message
void	error_no_file_or_dir(char *path, int is_cd)
{
	if (is_cd)
		str_print_error(127, path, ": cd: No such file or directory", NULL);
	else
		str_print_error(127, path, ": No such file or directory", NULL);
	error(127);
}

int	return_no_file_or_dir(char *path, int is_cd)
{
	if (is_cd)
		return (str_print_error(127,
				path, ": cd: No such file or directory", NULL));
	return (str_print_error(127, path, ": No such file or directory", NULL));
}
