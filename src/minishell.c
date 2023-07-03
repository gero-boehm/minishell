/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 08:59:40 by christianme       #+#    #+#             */
/*   Updated: 2023/07/03 14:06:55 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// *--EXECV--*
	char *cmd_args[] = {"echo", "test", NULL};
	printf("exec: %i\n", ft_exec(cmd_args));
	// printf("path: %s\n", cmd_path);

	// *--PROMPT--*
	// ft_prompt();



	return(0);
}