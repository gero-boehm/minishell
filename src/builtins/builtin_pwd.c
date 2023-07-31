/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:30:06 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/26 16:28:14 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "builtins.h"
#include "global.h"

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 1);
	if (pwd == NULL)
		error(errno);
	printf("%s\n", pwd);
	error(0);
}
